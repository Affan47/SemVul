on_node_loaded (AnjutaPmProject *sender, AnjutaProjectNode *node, gboolean complete, GError *error, GbfProjectView *view)
{
	if (error != NULL)
	{
		g_warning ("unable to load node");
		g_signal_emit (G_OBJECT (view), NODE_LOADED, 0, NULL, complete, error);
	}
	else
	{
		GtkTreeIter iter;
		gboolean found;

		gtk_tree_sortable_set_sort_column_id (GTK_TREE_SORTABLE (view->model),
		                                      GTK_TREE_SORTABLE_UNSORTED_SORT_COLUMN_ID,
		                                      GTK_SORT_ASCENDING);

		found = gbf_project_model_find_node (view->model, &iter, NULL, node);
		if (!found)
		{
			if (anjuta_project_node_parent (node) != NULL)
			{
				g_critical ("Unable to find node %s", anjuta_project_node_get_name (node));
			}
			else
			{
				GtkTreePath *path;
				GtkTreePath *child_path;
				GtkTreeModelFilter *filter;

				if (!gbf_project_model_find_child_name (view->model, &iter, NULL, anjuta_project_node_get_name (node)))
				{
					gbf_project_model_add_node (view->model, node, NULL, 0);
					gtk_tree_model_get_iter_first (GTK_TREE_MODEL (view->model), &iter);
				}
				else
				{
					GbfTreeData *data;
					GbfTreeData *new_data;


					gtk_tree_model_get (GTK_TREE_MODEL (view->model), &iter,
						GBF_PROJECT_MODEL_COLUMN_DATA, &data,
						-1);
					new_data = gbf_tree_data_new_node (node);
					gtk_tree_store_set (GTK_TREE_STORE (view->model), &iter,
								GBF_PROJECT_MODEL_COLUMN_DATA, new_data,
								-1);
					gbf_tree_data_free (data);
					gbf_project_view_update_tree (view, node, &iter);
				}


				path = gtk_tree_model_get_path (GTK_TREE_MODEL (view->model), &iter);
				filter = GTK_TREE_MODEL_FILTER (gtk_tree_view_get_model (GTK_TREE_VIEW (view)));
				child_path = gtk_tree_model_filter_convert_child_path_to_path (filter, path);
				if (child_path != NULL) gtk_tree_view_expand_row (GTK_TREE_VIEW (view), child_path, FALSE);
				gtk_tree_path_free (child_path);
				gtk_tree_path_free (path);
			}
		}
		else
		{
			gbf_project_view_update_tree (view, node, &iter);
		}
		gtk_tree_sortable_set_sort_column_id (GTK_TREE_SORTABLE (view->model),
		                                      GTK_TREE_SORTABLE_DEFAULT_SORT_COLUMN_ID,
		                                      GTK_SORT_ASCENDING);

		g_signal_emit (G_OBJECT (view), signals[NODE_LOADED], 0, found ? &iter : NULL, complete, NULL);
	}

	if (complete)
	{

		gbf_project_model_set_default_shortcut (view->model, TRUE);
	}
}
