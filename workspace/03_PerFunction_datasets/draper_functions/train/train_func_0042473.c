getDefaultPageMargin(UT_Dimension dim)
{
	switch(dim)
	{
	case DIM_IN:
		return "1.0in";
	case DIM_CM:
		return "2.54cm";
	case DIM_PI:
		return "6.0pi";
	case DIM_PT:
		return "72.0pt";
	case DIM_MM:
		return "25.4mm";


#if 0
	case DIM_PX:
	case DIM_PERCENT:
#endif
	case DIM_none:
	default:
		return "1.0in";
	}
}
