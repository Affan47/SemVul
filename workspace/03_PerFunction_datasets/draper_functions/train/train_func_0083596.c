tag_apply_selected_toggled(GtkCellRendererToggle *widget,
		gchar *path,
		GtkWidget *list_view)
{
	GtkTreeIter iter;
	GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(list_view));
	gboolean enabled = TRUE, set = FALSE;
	gpointer tmp;
	gint tag_id;
	SummaryView *summaryview = NULL;

	if (applywindow.busy)
		return;

	if (mainwindow_get_mainwindow() != NULL)
		summaryview = mainwindow_get_mainwindow()->summaryview;

	if (!gtk_tree_model_get_iter_from_string(model, &iter, path))
		return;

	gtk_tree_model_get(model, &iter,
			   TAG_SELECTED, &enabled,
			   TAG_DATA, &tmp,
			   -1);

	set = !enabled;
	tag_id = GPOINTER_TO_INT(tmp);

	gtk_list_store_set(GTK_LIST_STORE(model), &iter,
			   TAG_SELECTED, set,
			   TAG_SELECTED_INCONSISTENT, FALSE,
			   -1);

	APPLYWINDOW_LOCK();
	if (summaryview)
		summary_set_tag(summaryview, set ? tag_id : -tag_id, NULL);
	APPLYWINDOW_UNLOCK();
}
