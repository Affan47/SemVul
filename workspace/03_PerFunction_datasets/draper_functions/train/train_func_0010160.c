wrap_lines_toggled_cb (GtkAction *action,
		       gpointer   user_data)
{
	g_return_if_fail (GTK_IS_TOGGLE_ACTION (action) && GTK_SOURCE_IS_VIEW (user_data));
	gtk_text_view_set_wrap_mode (user_data,
				     gtk_toggle_action_get_active (GTK_TOGGLE_ACTION (action)) ?
					GTK_WRAP_WORD : GTK_WRAP_NONE);
}
