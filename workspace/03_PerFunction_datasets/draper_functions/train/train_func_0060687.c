paint(GanvCanvasBase* canvas)
{
	for (GSList* l = canvas->redraw_region; l; l = l->next) {
		IRect* rect = (IRect*)l->data;

		const GdkRectangle gdkrect = {
			rect->x + canvas->zoom_xofs,
			rect->y + canvas->zoom_yofs,
			rect->width,
			rect->height
		};

		gdk_window_invalidate_rect(canvas->layout.bin_window, &gdkrect, FALSE);
		g_free(rect);
	}

	g_slist_free(canvas->redraw_region);
	canvas->redraw_region = NULL;
	canvas->need_redraw = FALSE;

	canvas->redraw_x1 = 0;
	canvas->redraw_y1 = 0;
	canvas->redraw_x2 = 0;
	canvas->redraw_y2 = 0;
}
