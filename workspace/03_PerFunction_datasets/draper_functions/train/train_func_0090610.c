backtrace_select(GtkTreeSelection *sel, void *data)
{
	GtkTreeModel		*model;
	GtkTreeIter		iter;
	struct latency_line	*line = NULL;

	sel = gtk_tree_view_get_selection(GTK_TREE_VIEW(results_view));
	if (gtk_tree_selection_get_selected(sel, &model, &iter))
		gtk_tree_model_get(model, &iter, COL_R_LINE, &line, -1);
	if (ignore_sel)
		return TRUE;

	gtk_list_store_clear(backtrace_model);
	if (line)
		insert_backtrace(line);

	return TRUE;
}
