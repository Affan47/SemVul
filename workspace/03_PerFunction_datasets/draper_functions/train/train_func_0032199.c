GMT_left_conic (double y)
{
	double x_ws, y_ws, x_wn, y_wn, dy;

	GMT_geo_to_xy (project_info.w, project_info.s, &x_ws, &y_ws);
	GMT_geo_to_xy (project_info.w, project_info.n, &x_wn, &y_wn);
	dy = y_wn - y_ws;
	if (GMT_IS_ZERO (dy)) return (0.0);
	return (x_ws + ((x_wn - x_ws) * (y - y_ws) / dy));
}
