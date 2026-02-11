GMT_fancy_map_boundary (double w, double e, double s, double n)
{
	double fwidth;
	GMT_LONG dual = FALSE;
	GMT_LONG fat_pen, thin_pen;

	if (gmtdefs.basemap_type == GMT_IS_PLAIN) {
		GMT_wesn_map_boundary (w, e, s, n);
		return;
	}

	ps_setpaint (gmtdefs.basemap_frame_rgb);

	fwidth = fabs (gmtdefs.frame_width);
	if (frame_info.axis[1].item[GMT_TICK_LOWER].active) {
		fwidth *= 0.5;
		dual = TRUE;
	}

	fat_pen = irint (fwidth * gmtdefs.dpi);
	thin_pen = irint (0.1 * fwidth * gmtdefs.dpi);

	ps_setline (thin_pen);

	(void) GMT_fancy_frame_straight_outline (w, s, e, s, 0, dual);
	(void) GMT_fancy_frame_straight_outline (e, s, e, n, 1, dual);
	(void) GMT_fancy_frame_straight_outline (e, n, w, n, 2, dual);
	(void) GMT_fancy_frame_straight_outline (w, n, w, s, 3, dual);

	GMT_rounded_framecorners (w, e, s, n, 270.0, 90.0, dual);


	ps_setline(fat_pen);

	GMT_fancy_frame_straightlat_checkers (w, e, s, n, 90.0, 90.0, dual);
	GMT_fancy_frame_straightlon_checkers (w, e, s, n, 180.0, 0.0, dual);

	ps_setline (thin_pen);
}
