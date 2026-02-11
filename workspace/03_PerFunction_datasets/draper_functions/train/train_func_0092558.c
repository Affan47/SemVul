nautilus_list_view_get_backing_uri (NautilusView *view)
{
	NautilusListView *list_view;
	NautilusListModel *list_model;
	NautilusFile *file;
	GtkTreeView *tree_view;
	GtkTreeSelection *selection;
	GtkTreePath *path;
	GList *paths;
	guint length;
	char *uri;

	g_return_val_if_fail (NAUTILUS_IS_LIST_VIEW (view), NULL);

	list_view = NAUTILUS_LIST_VIEW (view);
	list_model = list_view->details->model;
	tree_view = list_view->details->tree_view;

	g_assert (list_model);


	uri = NULL;

	selection = gtk_tree_view_get_selection (tree_view);
	length = gtk_tree_selection_count_selected_rows (selection);

	if (length == 1) {

		paths = gtk_tree_selection_get_selected_rows (selection, NULL);
		path = (GtkTreePath *) paths->data;

		file = nautilus_list_model_file_for_path (list_model, path);
		if (file == NULL) {

			gtk_tree_path_up (path);
			file = nautilus_list_model_file_for_path (list_model, path);
		}

		if (file != NULL) {
			if (nautilus_file_is_directory (file) &&
			    gtk_tree_view_row_expanded (tree_view, path)) {
				uri = nautilus_file_get_uri (file);
			}
			nautilus_file_unref (file);
		}

		gtk_tree_path_free (path);
		g_list_free (paths);
	}

	if (uri == NULL && length > 0) {

		gboolean is_common, is_root;


		tree_selection_has_common_parent (selection, &is_common, &is_root);

		if (is_common && !is_root) {
			paths = gtk_tree_selection_get_selected_rows (selection, NULL);
			path = (GtkTreePath *) paths->data;

			file = nautilus_list_model_file_for_path (list_model, path);
			g_assert (file != NULL);
			uri = nautilus_file_get_parent_uri (file);
			nautilus_file_unref (file);

			g_list_free_full (paths, (GDestroyNotify) gtk_tree_path_free);
		}
	}

	if (uri != NULL) {
		return uri;
	}

	return NAUTILUS_VIEW_CLASS (nautilus_list_view_parent_class)->get_backing_uri (view);
}
