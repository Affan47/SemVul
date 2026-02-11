tree_view_row_make_visible(GtkTreeView *widget, GtkTreeIter *iter, gboolean center)
{
	GtkTreePath *tpath;
	gint vis;

	vis = tree_view_row_get_visibility(widget, iter, TRUE);

	tpath = gtk_tree_model_get_path(gtk_tree_view_get_model(widget), iter);
	if (center && vis != 0)
		{
		gtk_tree_view_scroll_to_cell(widget, tpath, NULL, TRUE, 0.5, 0.0);
		}
	else if (vis < 0)
		{
		gtk_tree_view_scroll_to_cell(widget, tpath, NULL, TRUE, 0.0, 0.0);
		}
	else if (vis > 0)
		{
		gtk_tree_view_scroll_to_cell(widget, tpath, NULL, TRUE, 1.0, 0.0);
		}
	gtk_tree_path_free(tpath);

	return vis;
}
