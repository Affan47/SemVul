GMT_rounded_framecorners (double w, double e, double s, double n, double anglew, double anglee, GMT_LONG secondary_too)
{
	GMT_LONG k;
	double x, y, width;

	if (gmtdefs.basemap_type != GMT_IS_ROUNDED) return;

	width = ((secondary_too) ? 0.5 : 1.0) * fabs (gmtdefs.frame_width);
	for (k = 0; k < 1 + secondary_too; k++) {
		if (frame_info.side[0] && frame_info.side[1]) {
			GMT_geo_to_xy (e, s, &x, &y);
			ps_arc (x, y, (k+1)*width, 180.0+anglee, 270.0+anglee, PSL_ARC_DRAW);
		}
		if (frame_info.side[1] && frame_info.side[2]) {
			GMT_geo_to_xy (e, n, &x, &y);
			ps_arc (x, y, (k+1)*width, 270.0+anglee, 360.0+anglee, PSL_ARC_DRAW);
		}
		if (frame_info.side[2] && frame_info.side[3]) {
			GMT_geo_to_xy (w, n, &x, &y);
			ps_arc (x, y, (k+1)*width, 180.0+anglew, 270.0+anglew, PSL_ARC_DRAW);
		}
		if (frame_info.side[3] && frame_info.side[0]) {
			GMT_geo_to_xy (w, s, &x, &y);
			ps_arc (x, y, (k+1)*width, 270.0+anglew, 360.0+anglew, PSL_ARC_DRAW);
		}
		if ((GMT_IS_AZIMUTHAL || GMT_IS_CONICAL) && frame_info.side[3] && frame_info.side[1]) {
			if (GMT_IS_ZERO (project_info.n - 90.0)) {
				GMT_geo_to_xy (w, n, &x, &y);
				ps_arc (x, y, (k+1)*width, anglee, 180.0+anglew, PSL_ARC_DRAW);
			}
			else if (GMT_IS_ZERO (project_info.s + 90.0)) {
				GMT_geo_to_xy (w, s, &x, &y);
				ps_arc (x, y, (k+1)*width, anglew-90.0, anglee-90.0, PSL_ARC_DRAW);
			}
		}
	}
}
