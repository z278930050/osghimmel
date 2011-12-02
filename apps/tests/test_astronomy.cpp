
// Copyright (c) 2011, Daniel M�ller <dm@g4t3.de>
// Computer Graphics Systems Group at the Hasso-Plattner-Institute, Germany
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
//   * Redistributions of source code must retain the above copyright notice, 
//     this list of conditions and the following disclaimer.
//   * Redistributions in binary form must reproduce the above copyright 
//     notice, this list of conditions and the following disclaimer in the 
//     documentation and/or other materials provided with the distribution.
//   * Neither the name of the Computer Graphics Systems Group at the 
//     Hasso-Plattner-Institute (HPI), Germany nor the names of its 
//     contributors may be used to endorse or promote products derived from 
//     this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE 
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
// POSSIBILITY OF SUCH DAMAGE.


#include "test_astronomy.h"

#include "include/mathmacros.h"
#include "include/atime.h"
#include "include/julianday.h"
#include "include/sideraltime.h"
#include "include/coords.h"

#include "include/moon.h"
#include "include/sun.h"
#include "include/earth.h"


void test_aTime();
void test_jd();
void test_sideralTime();
void test_coords();


void test_astronomy()
{
    // Run Tests.
    test_aTime();
    test_jd();
    test_sideralTime();
    test_coords();

    TEST_REPORT();
}


void test_aTime()
{
    // Test decimal day time.
    t_aTime aTime0(1957, 10, 4.81);

    ASSERT_EQ(__int64, 4, aTime0.day);
    ASSERT_EQ(__int64, 19, aTime0.hour);
    ASSERT_EQ(__int64, 26, aTime0.minute);
    ASSERT_EQ(__int64, 24, aTime0.second);

    // Test decimal day time:.
    t_aTime aTime1(2000, 1, 1);

    ASSERT_EQ(__int64, 1, aTime1.day);
    ASSERT_EQ(__int64, 0, aTime1.hour);
    ASSERT_EQ(__int64, 0, aTime1.minute);
    ASSERT_EQ(__int64, 0, aTime1.second);
}


void test_jd()
{
    // Times from "Astronomical Algorithms" - Chapter 7

    // Test some dates.

    // Standard equinox (decimal day time).
    ASSERT_EQ(long double, 2436116.31,jd(t_aTime(1957, 10,  4.81)));
    ASSERT_EQ(long double, 1842713.0, jd(t_aTime( 333,  1, 27, 12, 0, 0)));
    
    // Test some dates.
    ASSERT_EQ(long double, 2451545.0, jd(t_aTime( 2000,  1,  1.5)));
    ASSERT_EQ(long double, 2446822.5, jd(t_aTime( 1987,  1, 27.0)));
    ASSERT_EQ(long double, 2446966.0, jd(t_aTime( 1987,  6, 19.5)));
    ASSERT_EQ(long double, 2447187.5, jd(t_aTime( 1988,  1, 27.0)));
    ASSERT_EQ(long double, 2447332.0, jd(t_aTime( 1988,  6, 19.5)));
    ASSERT_EQ(long double, 2443259.9, jd(t_aTime( 1977,  4, 26.4)));
    ASSERT_EQ(long double, 2415020.5, jd(t_aTime( 1900,  1,  1.0)));
    ASSERT_EQ(long double, 2305447.5, jd(t_aTime( 1600,  1,  1.0)));
    ASSERT_EQ(long double, 2305812.5, jd(t_aTime( 1600, 12, 31.0)));
    ASSERT_EQ(long double, 2026871.8, jd(t_aTime(  837,  4, 10.3)));
    ASSERT_EQ(long double, 1356001.0, jd(t_aTime(-1000,  7, 12.5)));
    ASSERT_EQ(long double, 1355866.5, jd(t_aTime(-1000,  2, 29.0)));
    ASSERT_EQ(long double, 1355671.4, jd(t_aTime(-1001,  8, 17.9)));
    ASSERT_EQ(long double,       0.0, jd(t_aTime(-4712,  1,  1.5)));


    // Times from WikiPedia
    ASSERT_EQ(long double, 1721423.5000, jd(t_aTime(   1,  1,  1,  0,  0,  0)));
    ASSERT_EQ(long double, 1842713.0000, jd(t_aTime( 333,  1, 27, 12,  0,  0)));
    // Check Calendar Swap.
    ASSERT_EQ(long double, 2299160.5000, jd(t_aTime(1582, 10,  4, 24,  0,  0)));
    ASSERT_EQ(long double, 2299160.5000, jd(t_aTime(1582, 10, 15,  0,  0,  0)));
    // Check from http://www.stjarnhimlen.se/comp/tutorial.html.
    ASSERT_EQ(long double, 2448000.5000, jd(t_aTime(1990,  4, 19,  0,  0,  0))); 

    // Test some dates.
    ASSERT_EQ(long double, 2415020.5000, jd(t_aTime(1900,  1,  1,  0,  0,  0))); 
    ASSERT_EQ(long double, 2447893.0000, jd(t_aTime(1990,  1,  1, 12,  0,  0))); 
    ASSERT_EQ(long double, 2447893.2500, jd(t_aTime(1990,  1,  1, 18,  0,  0))); 

    // Standard Equinox.
    ASSERT_EQ(long double, 2451545.0000, jd(t_aTime(2000,  1,  1, 12,  0,  0))); 

    ASSERT_EQ(long double, 2453750.1875, jd(t_aTime(2006,  1, 14, 16, 30,  0))); 
    ASSERT_EQ(long double, 2455281.1875, jd(t_aTime(2010,  3, 25, 16, 30,  0))); 

    // Check undefined days.
    ASSERT_EQ(long double,      0.0000, jd(t_aTime(1582, 10,  5,  0,  0,  0))); 
    ASSERT_EQ(long double,      0.0000, jd(t_aTime(1582, 10, 14,  0,  0,  0))); 


    // Test mjd;
    ASSERT_EQ(long double,       0.0, mjd(t_aTime(1858, 11, 17.0)));




    // Test julianday to aTime.

    t_aTime aTime0 = makeTime(2436116.31);
    
    ASSERT_EQ(__int64, 1957, aTime0.year);
    ASSERT_EQ(__int64,   10, aTime0.month);
    ASSERT_EQ(__int64,    4, aTime0.day);
    ASSERT_EQ(__int64,   19, aTime0.hour);
    ASSERT_EQ(__int64,   26, aTime0.minute);
    ASSERT_EQ(__int64,   24, aTime0.second);

    ASSERT_AB(long double, 4.81, aTime0.dayf(), 0.000000001);


    t_aTime aTime1 = makeTime(1842713.0);
    
    ASSERT_EQ(__int64,  333, aTime1.year);
    ASSERT_EQ(__int64,    1, aTime1.month);
    ASSERT_EQ(__int64,   27, aTime1.day);
    ASSERT_EQ(__int64,   12, aTime1.hour);
    ASSERT_EQ(__int64,    0, aTime1.minute);
    ASSERT_EQ(__int64,    0, aTime1.second);

    ASSERT_EQ(long double, 27.5, aTime1.dayf());


    t_aTime aTime2 = makeTime(1507900.13);
    
    ASSERT_EQ(__int64, -584, aTime2.year);
    ASSERT_EQ(__int64,    5, aTime2.month);
    ASSERT_EQ(__int64,   28, aTime2.day);
    ASSERT_EQ(__int64,   15, aTime2.hour);
    ASSERT_EQ(__int64,    7, aTime2.minute);
    ASSERT_EQ(__int64,   12, aTime2.second);

    ASSERT_EQ(long double, 28.63, aTime2.dayf());
}


void test_sideralTime()
{
    ASSERT_AB(long double, _hour(13, 10, 46.3668), siderealTime(t_aTime(1987, 4, 10,  0,  0, 0)), 0.00000001);
    ASSERT_AB(long double, _hour( 8, 34, 57.0896), siderealTime(t_aTime(1987, 4, 10, 19, 21, 0)), 0.00000001);
}


void test_coords()
{
    t_julianDay t;

    // Test nutation and obliquity.

    t = jd(t_aTime(1987,  4, 10, 0, 0, 0));

    ASSERT_AB(long double, -0.127296372348, jCenturiesSinceSE(t),            0.00000001);
    ASSERT_AB(long double, _decimal(23, 26, 27.407), earth_meanObliquity(t), 0.000001);

    ASSERT_AB(long double, _decimal( 0,  0,  9.443), earth_obliquityNutation(t), 0.00005);
    ASSERT_AB(long double, _decimal(23, 26, 36.850), earth_trueObliquity(t),     0.00005);

    ASSERT_AB(long double, _decimal( 0,  0, -3.788), earth_longitudeNutation(t), 0.00005);

    ASSERT_AB(long double, 229.27840, moon_meanAnomaly(t),  0.00002);


    t = jd(t_aTime(1992, 10, 13, 0, 0, 0));

    ASSERT_AB(long double, -0.072183436, jCenturiesSinceSE(t), 0.00000001);

    ASSERT_AB(long double, 201.80719, sun_meanLongitude(t),   0.00001);
    ASSERT_AB(long double, 278.99396, sun_meanAnomaly(t),     0.00001);
    ASSERT_AB(long double,  -1.89732, sun_center(t),          0.00001);
    ASSERT_AB(long double, 199.90987, sun_trueLongitude(t),   0.00001);
    ASSERT_AB(long double,  23.44023, earth_meanObliquity(t), 0.000001);

    ASSERT_AB(long double, 0.99766, earth_sunDistance(t),     0.00001);

    ASSERT_AB(long double, 0.016711651, earth_orbitEccentricity(t), 0.00000001);


    t_equCoords equ = sun_apparentPosition(t);

    ASSERT_AB(long double,  13.225388, _hours(equ.right_ascension), 0.00005);
    ASSERT_AB(long double, - 7.78507 , equ.declination,             0.00005);
}