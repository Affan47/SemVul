gedit_window_key_press_event (GtkWidget   *widget,
			      GdkEventKey *event)
{
	static gpointer grand_parent_class = NULL;

	GtkWindow *window = GTK_WINDOW (widget);
	gboolean handled = FALSE;

	if (grand_parent_class == NULL)
	{
		grand_parent_class = g_type_class_peek_parent (gedit_window_parent_class);
	}


	if (!handled)
	{
		handled = gtk_window_propagate_key_event (window, event);
	}


	if (!handled)
	{
		handled = gtk_window_activate_key (window, event);
	}


	if (!handled)
	{
		handled = GTK_WIDGET_CLASS (grand_parent_class)->key_press_event (widget, event);
	}

	if (!handled)
	{
		return gedit_app_process_window_event (GEDIT_APP (g_application_get_default ()),
		                                       GEDIT_WINDOW (widget),
		                                       (GdkEvent *)event);
	}

	return TRUE;
}
