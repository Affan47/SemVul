draw_chartdata_lines(GkrellmChart *cp, GkrellmChartdata *cd, gint i0)
	{
	gint	n, x, xp, y, y0, y1;

	y0 = chartdata_ycoord(cp, cd, 0);
	for (n = i0; n < cp->w; ++n)
		{
		x = computed_index(cp, n);
		y1 = chartdata_ycoord(cp, cd, cd->data[x]);
		if (n == 0)
			cd->y_p = y1;
		else if (!cd->y_p_valid && i0 == cp->w - 1)
			{
			if ((xp = x - 1) < 0)
				xp = cp->w - 1;
			cd->y_p = cd->y_pp = chartdata_ycoord(cp, cd, cd->data[xp]);
			}
		y = fix_y(y1, cd->y_p, cd->y_pp);
		cd->y_pp = y;
		cd->y_p = y1;
		cd->y_p_valid = FALSE;
		if (cd->data[x] > 0 || (cd->inverted ? (y > y0) : (y < y0)))
			{
			if (y == y1)
				gdk_draw_point(cd->data_bitmap, _GK.bit1_GC, cp->x + n, y1);
			else
				gdk_draw_line(cd->data_bitmap, _GK.bit1_GC,
						cp->x + n, y, cp->x + n, y1);
			}
		}


	if (cd->maxval > 0)
		{
		y0 = chartdata_ycoord(cp, cd, 0);
		y1 = chartdata_ycoord(cp, cd, cd->maxval);
		gdk_gc_set_clip_mask(_GK.draw1_GC, cd->data_bitmap);
		if (cd->inverted)
			gdk_draw_drawable(cp->pixmap, _GK.draw1_GC, cd->layer.pixmap,
					0, y0,  0, y0,  cp->w, y1 - y0 + 1);
		else
			gdk_draw_drawable(cp->pixmap, _GK.draw1_GC, cd->layer.pixmap,
					0, y1,  0, y1,  cp->w, y0 - y1 + 1);
		}
	}
