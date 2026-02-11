getMoonRiseSet(UBool rise)
{
    MoonRiseSetCoordFunc func;
    return riseOrSet(func,
                     rise,
                     .533 * DEG_RAD,
                     34 /60.0 * DEG_RAD,
                     MINUTE_MS);
}
