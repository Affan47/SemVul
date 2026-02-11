sharedlibs_show (Sharedlibs* sl)
{
	if(sl)
	{
		if(sl->is_showing)
		{
			gdk_window_raise(gtk_widget_get_window (sl->widgets.window));
		}
		else
		{
			gtk_window_move(GTK_WINDOW(sl->widgets.window), sl->win_pos_x,
									 sl->win_pos_y);
			gtk_window_set_default_size(GTK_WINDOW(sl->widgets.window),
										sl->win_width, sl->win_height);
			gtk_widget_show(sl->widgets.window);
			sl->is_showing = TRUE;
			dma_queue_info_sharedlib (
					sl->debugger,
					(IAnjutaDebuggerCallback)sharedlibs_update,
					sl);
		}
	}
}
