gmttrack_outside (int lon, int lat, int w, int e, int s, int n)
{
	if (lat < s || lat > n) return (TRUE);
	lon -= 360000000;
	while (lon < w) lon += 360000000;
	if (lon > e) return (TRUE);
	return (FALSE);
}
