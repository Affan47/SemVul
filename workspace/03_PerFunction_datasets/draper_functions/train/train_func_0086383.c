yes_dndopen_cb(GtkWidget *widget, gpointer data)
{
	destroy_yesno_dialog(widget);

	if (!gtk_term_is_named(term))
		file_select(GTK_FILE_CHOOSER_ACTION_SAVE,
					"Save Notebook As ...", "*.en", "untitled",
					G_CALLBACK(save_as_dndopen_cb), term_window);
	else {
		gtk_term_save(term,NULL);
		gtk_term_load(term, dnd_path);
		chdir(g_dirname(dnd_path));
	}
}
