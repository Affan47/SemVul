copy_to_clipboard(GtkTreeModel *model, GtkTreePath *unused_path,
		GtkTreeIter *iter, gpointer unused_data)
{
	char *text = NULL;

	(void) unused_path;
	(void) unused_data;

   	gtk_tree_model_get(model, iter, 0, &text, (-1));
	clipboard_set_text(gui_main_window(), text);
	G_FREE_NULL(text);
}
