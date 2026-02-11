ganv_canvas_base_get_scroll_region(GanvCanvasBase* canvas, double* x1, double* y1, double* x2,
                                   double* y2)
{
	g_return_if_fail(GANV_IS_CANVAS_BASE(canvas));

	if (x1) {
		*x1 = canvas->scroll_x1;
	}

	if (y1) {
		*y1 = canvas->scroll_y1;
	}

	if (x2) {
		*x2 = canvas->scroll_x2;
	}

	if (y2) {
		*y2 = canvas->scroll_y2;
	}
}
