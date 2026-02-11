expanded_list_button_press_event_cb (GtkStatusIcon  *status_icon,
		 	 	     GdkEventButton *event,
				     gpointer        user_data)
{
	GthTagsEntry *self = user_data;

	if (event->button == 3) {
		gtk_menu_popup (GTK_MENU (self->priv->expanded_list.popup_menu),
				NULL,
				NULL,
				NULL,
				NULL,
				event->button,
				event->time);
		return FALSE;
	}

	return FALSE;
}
