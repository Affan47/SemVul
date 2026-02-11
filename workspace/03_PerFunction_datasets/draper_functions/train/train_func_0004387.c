logical_width(int width)
{
	int divider = 1;

#ifdef UNANGBAND
	if (use_trptile) divider = 3;
	else if (use_dbltile) divider = 2;
#endif

	if (use_bigtile) divider *= 2;

	return width / divider;
}
