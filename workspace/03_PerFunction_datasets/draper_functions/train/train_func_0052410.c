on_file_save_as(GtkAction *action)
{
	file_select(GTK_FILE_CHOOSER_ACTION_SAVE,
				"Save Notebook As ...", "*.en", gtk_term_is_named(term) ? gtk_term_get_name(term) : "untitled",
				G_CALLBACK(save_as_cb), term_window);
}
