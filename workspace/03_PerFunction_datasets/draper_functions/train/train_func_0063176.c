net_expose_event(GtkWidget *widget, GdkEventExpose *ev)
	{
	GList		*list;
	NetMon		*net;
	GdkPixmap	*pixmap	= NULL;

	if (timer_panel->drawing_area == widget)
		pixmap = timer_panel->pixmap;
	else
		for (list = net_mon_list; list; list = list->next)
			{
			net = (NetMon *) list->data;
			if (!net->chart || !net->chart->panel)
				continue;
			if (net->chart->drawing_area == widget)
				pixmap = net->chart->pixmap;
			else if (net->chart->panel->drawing_area == widget)
				pixmap = net->chart->panel->pixmap;
			if (pixmap)
				break;
			}
	if (pixmap)
		gdk_draw_drawable(widget->window, gkrellm_draw_GC(1), pixmap,
			ev->area.x, ev->area.y, ev->area.x, ev->area.y,
			ev->area.width, ev->area.height);
	return FALSE;
	}
