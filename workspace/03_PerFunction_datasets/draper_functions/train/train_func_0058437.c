file_chooser_response (GtkDialog *dialog,
                       gint response_id,
                       GtkFileChooser *button)
{
	g_return_if_fail (button != NULL);

	if (response_id == GTK_RESPONSE_NO)
		gtk_file_chooser_unselect_all (button);
}
