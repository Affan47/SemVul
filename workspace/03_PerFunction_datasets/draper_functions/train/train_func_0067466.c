proc_expose_event(GtkWidget *widget, GdkEventExpose *ev)
	{
	GkrellmChart	*cp		= proc.chart;
	GdkPixmap		*pixmap	= NULL;

	if (cp)
		{
		if (widget == cp->drawing_area)
			pixmap = cp->pixmap;
		else if (widget == cp->panel->drawing_area)
			pixmap = cp->panel->pixmap;
		}
	if (pixmap)
		gdk_draw_drawable(widget->window, gkrellm_draw_GC(1), pixmap,
				  ev->area.x, ev->area.y, ev->area.x, ev->area.y,
				  ev->area.width, ev->area.height);
	return FALSE;
	}
