completion_match_selected(GtkEntryCompletion *widget, GtkTreeModel *model,
										  GtkTreeIter *iter, gpointer user_data)
{
	gchar *str;
	gtk_tree_model_get(model, iter, FILEVIEW_COLUMN_NAME, &str, -1);
	if (str != NULL)
	{
		gchar *text = g_strconcat(current_dir, G_DIR_SEPARATOR_S, str, NULL);
		gtk_entry_set_text(GTK_ENTRY(path_entry), text);
		gtk_editable_set_position(GTK_EDITABLE(path_entry), -1);

		on_path_entry_activate(GTK_ENTRY(path_entry), NULL);
		g_free(text);
	}
	g_free(str);

	return TRUE;
}
