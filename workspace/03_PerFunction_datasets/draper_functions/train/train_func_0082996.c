ganv_canvas_base_window_to_world(GanvCanvasBase* canvas, double winx, double winy,
                                 double* worldx, double* worldy)
{
	g_return_if_fail(GANV_IS_CANVAS_BASE(canvas));

	if (worldx) {
		*worldx = canvas->scroll_x1 + ((winx - canvas->zoom_xofs)
		                               / canvas->pixels_per_unit);
	}

	if (worldy) {
		*worldy = canvas->scroll_y1 + ((winy - canvas->zoom_yofs)
		                               / canvas->pixels_per_unit);
	}
}
