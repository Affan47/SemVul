view_seek_selected(GtkTreeSelection *selection, gboolean focus, SeekerType seeker)
{
	GtkTreeModel *model;
	GtkTreeIter iter;

	if (gtk_tree_selection_get_selected(selection, &model, &iter))
	{
		char *file;
		gint line;

		gtk_tree_model_get(model, &iter, COLUMN_FILE, &file, COLUMN_LINE, &line, -1);

		if (file)
		{
			utils_seek(file, line, focus, seeker);
			g_free(file);
		}
	}
}
