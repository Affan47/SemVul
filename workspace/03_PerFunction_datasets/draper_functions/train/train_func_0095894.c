glade_fixed_child_event (GladeWidget *gwidget,
			 GdkEvent    *event,
			 GladeFixed  *fixed)
{
	GtkWidget *event_widget;


	gdk_window_get_user_data (((GdkEventAny *)event)->window, (gpointer)&event_widget);


	if (fixed->configuring)
	{
		return glade_fixed_handle_child_event
			(fixed, fixed->configuring, event_widget, event);
	}

	g_return_val_if_fail (GLADE_IS_WIDGET (gwidget), FALSE);


	if (GLADE_IS_FIXED (gwidget) &&
	    glade_app_get_pointer_mode() == GLADE_POINTER_ADD_WIDGET)
	{
		glade_cursor_set (((GdkEventAny *)event)->window,
				  GLADE_CURSOR_ADD_WIDGET);
		return FALSE;
	}

	return glade_fixed_handle_child_event
		(fixed, gwidget, event_widget, event);

}
