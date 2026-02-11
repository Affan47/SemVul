settings_close_callback(GtkDialog *dialog_box,
					gint response_id, gpointer user_data)
{
	if (response_id == GTK_RESPONSE_DELETE_EVENT ||
				response_id == GTK_RESPONSE_CLOSE)
		settings_cancel_callback(NULL, NULL);
}
