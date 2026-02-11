suppress_hidden_toggled(GtkWidget *widget, gpointer data)
{
	LOG(LOG_DEBUG, "IN : suppress_hidden_toggled()");

	bsuppress_hidden_files = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget));
	refresh_directory_tree();

	LOG(LOG_DEBUG, "OUT : suppress_hidden_toggled(%d)", bignore_case);

	return(FALSE);
}
