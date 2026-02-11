gpk_update_viewer_get_install_package_ids (void)
{
	PkInfoEnum info;
	gboolean child_valid;
	gboolean valid;
	gboolean update;
	gchar *package_id;
	GtkTreeIter child_iter;
	GtkTreeView *treeview;
	GtkTreeModel *model;
	GtkTreeIter iter;
	GPtrArray *array;

	treeview = GTK_TREE_VIEW(gtk_builder_get_object (builder, "treeview_updates"));
	model = gtk_tree_view_get_model (treeview);

	array = g_ptr_array_new ();


	valid = gtk_tree_model_get_iter_first (model, &iter);
	while (valid) {
		gtk_tree_model_get (model, &iter,
				    GPK_UPDATES_COLUMN_INFO, &info,
				    GPK_UPDATES_COLUMN_SELECT, &update,
				    GPK_UPDATES_COLUMN_ID, &package_id, -1);


		if (package_id != NULL &&
		    update &&
		    gpk_update_viewer_info_is_update_enum (info))
			g_ptr_array_add (array, package_id);
		else
			g_free (package_id);


		child_valid = gtk_tree_model_iter_children (model, &child_iter, &iter);
		while (child_valid) {
			gtk_tree_model_get (model, &child_iter,
					    GPK_UPDATES_COLUMN_INFO, &info,
					    GPK_UPDATES_COLUMN_SELECT, &update,
					    GPK_UPDATES_COLUMN_ID, &package_id, -1);


			if (update && gpk_update_viewer_info_is_update_enum (info))
				g_ptr_array_add (array, package_id);
			else
				g_free (package_id);

			child_valid = gtk_tree_model_iter_next (model, &child_iter);
		}

		valid = gtk_tree_model_iter_next (model, &iter);
	}
	return array;
}
