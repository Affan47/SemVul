chartdata_ycoord(GkrellmChart *cp, GkrellmChartdata *cd, gint yd)
	{
	glong	y;
	guint64	Y;

	if (cp->scale_max <= 0)
		cp->scale_max = 1;

	if (yd > 2000000000 / MAX_CHARTHEIGHT)
		{
		Y = (guint64) yd * (guint64) cd->h;
		y = Y / cp->scale_max;
		}
	else
		y = ((glong) yd * cd->h / cp->scale_max);

	if (y < 0)
		y = 0;
	if (y >= cd->h)
		y = cd->h - 1;
	if (cd->inverted)
		y = cd->h - y - 1;
	y += cd->y;
	return Y_SCREEN_MAP(cp, y);
	}
