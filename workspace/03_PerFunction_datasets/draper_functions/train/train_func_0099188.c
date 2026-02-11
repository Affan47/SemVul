nautilus_list_view_invert_selection (NautilusView *view)
{
	NautilusListView *list_view;
	GtkTreeSelection *tree_selection;
	GList *node;
	GList *iters, *l;
	NautilusFile *file;
	GList *selection = NULL;

	list_view = NAUTILUS_LIST_VIEW (view);
	tree_selection = gtk_tree_view_get_selection (list_view->details->tree_view);

	g_signal_handlers_block_by_func (tree_selection, list_selection_changed_callback, view);

	gtk_tree_selection_selected_foreach (tree_selection,
					     nautilus_list_view_get_selection_foreach_func, &selection);

	gtk_tree_selection_select_all (tree_selection);

	for (node = selection; node != NULL; node = node->next) {
		file = node->data;
		iters = nautilus_list_model_get_all_iters_for_file (list_view->details->model, file);

		for (l = iters; l != NULL; l = l->next) {
			gtk_tree_selection_unselect_iter (tree_selection,
							  (GtkTreeIter *)l->data);
		}
		g_list_free_full (iters, g_free);
	}

	g_list_free (selection);

	g_signal_handlers_unblock_by_func (tree_selection, list_selection_changed_callback, view);
	nautilus_view_notify_selection_changed (view);
}
