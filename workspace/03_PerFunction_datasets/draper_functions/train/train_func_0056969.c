cosines (double lat1, double lon1, double lat2, double lon2) {
    lat1 *= DEG_RADS; lon1 *= DEG_RADS;
    lat2 *= DEG_RADS; lon2 *= DEG_RADS;
    double a = sin(lat1) * sin(lat2);
    double b = cos(lat1) * cos(lat2) * cos(lon2 - lon1);
    double d = acos(a + b);

    if (isnan(d))
        return haversine(lat1, lon1, lat2, lon2);
    return d;
}
