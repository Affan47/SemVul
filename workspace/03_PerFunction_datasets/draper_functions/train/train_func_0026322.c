_findClosestThickness(const char *sthickness) const
{
	double thickness = UT_convertToInches(sthickness);
	guint i = 0;
	guint closest = 0;
	double dClose = 100000000.;
	for(i = 0; i < BORDER_SHADING_NUMTHICKNESS; i++)
	{
		double diff = thickness - m_dThickness[i];
		if(diff < 0)
			diff = -diff;
		if(diff < dClose)
		{
			closest = i;
			dClose = diff;
		}
	}
	return closest;
}
