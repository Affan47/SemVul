initWindow()
{


	if (!isTopLevel())
	{
		g_signal_connect(G_OBJECT(border), "configure-event", G_CALLBACK(cb_configure), (gpointer)this);
		g_signal_connect_after(G_OBJECT(border), "map", G_CALLBACK(cb_show), (gpointer)this);
		g_signal_connect(G_OBJECT(border),"unmap",G_CALLBACK(cb_hide),(gpointer)this);

		g_signal_connect(G_OBJECT(widget), "expose-event", G_CALLBACK(cb_expose), (gpointer)this);
		gtk_widget_add_events(border, GDK_STRUCTURE_MASK);
	}
	else
	{

		g_signal_connect(G_OBJECT(border), "show",G_CALLBACK(cb_show),(gpointer)this);
		g_signal_connect(G_OBJECT(border), "hide",G_CALLBACK(cb_hide),(gpointer)this);
		g_signal_connect(G_OBJECT(border), "configure-event",G_CALLBACK(cb_configure),(gpointer)this);
		g_signal_connect(G_OBJECT(border), "delete-event",G_CALLBACK(win_close),(gpointer)this);
		g_signal_connect(G_OBJECT(border), "window-state-event",G_CALLBACK(win_frame),(gpointer)this);

		gtk_widget_add_events(widget,GDK_BUTTON_MOTION_MASK);
		g_signal_connect(G_OBJECT(widget), "expose-event", G_CALLBACK(cb_expose), (gpointer)this);
	}

	gtk_window_add_accel_group(GTK_WINDOW(topLevel()->border), accel);

	have_cursor = true;
}
