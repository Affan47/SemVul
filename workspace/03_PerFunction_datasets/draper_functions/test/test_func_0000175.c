iluRegioniv(ILpointi *Points, ILuint n)
{
	if (Points == NULL || n == 0) {
		ifree(RegionPointsi);
		ifree(RegionPointsf);
		RegionPointsi = NULL;
		PointNum = 0;
		return;
	}
	if (n < 3) {
		ilSetError(ILU_INVALID_PARAM);
		return;
	}
	ifree(RegionPointsi);
	ifree(RegionPointsf);
	RegionPointsi = (ILpointi*)ialloc(sizeof(ILpointi) * n);
	if (RegionPointsi == NULL)
		return;
	memcpy(RegionPointsi, Points, sizeof(ILpointi) * n);
	PointNum = n;
	return;
}
