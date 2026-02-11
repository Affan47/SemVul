eel_pop_up_context_menu (GtkMenu *menu,
			 GdkEventButton *event)
{
	int button;

	g_return_if_fail (GTK_IS_MENU (menu));


	if (event) {
		button = event->type == GDK_BUTTON_RELEASE
			? 0
			: event->button;
	} else {
		button = 0;
	}

	gtk_menu_popup (menu,
			NULL,
			NULL,
			NULL,
			NULL,
			button,
			event ? event->time : gtk_get_current_event_time ());

	g_object_ref_sink (menu);
	g_object_unref (menu);
}
