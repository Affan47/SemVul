gtt_projects_tree_model_row_changed_callback (GtkTreeModel *model,
											  GtkTreePath *path,
											  GtkTreeIter *iter,
											  gpointer data)
{
	GttProjectsTree *gpt = GTT_PROJECTS_TREE (data);
	GttProject *prj = NULL;
	GttProject *parent = NULL;

	gtk_tree_model_get (model, iter, GTT_PROJECT_COLUMN, &prj, -1);

	if (prj)
	{
		int path_depth = gtk_tree_path_get_depth (path);
		gint *indices = gtk_tree_path_get_indices (path);
		int position = 0;
		if (indices)
		{
			position = indices[path_depth - 1];
		}
		else
		{
			g_message ("indices is NULL");
		}
		GtkTreeIter parent_iter;
		if (gtk_tree_model_iter_parent (model, &parent_iter, iter))
		{
			gtk_tree_model_get (model, &parent_iter, GTT_PROJECT_COLUMN, &parent, -1);
		}

		GttProjectsTreePrivate *priv = GTT_PROJECTS_TREE_GET_PRIVATE (gpt);
		GtkTreeRowReference *row_ref = (GtkTreeRowReference *) g_tree_lookup (priv->row_references, prj);
		if (row_ref)
		{
			GtkTreePath *ref_path = gtk_tree_row_reference_get_path (row_ref);


			if (gtk_tree_path_compare (path, ref_path))
			{
				gtt_project_reparent (prj, parent, position);
				row_ref = gtk_tree_row_reference_new (model, path);
				g_tree_insert (priv->row_references, prj, row_ref);
			}
		}
	}
}
