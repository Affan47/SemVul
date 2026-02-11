setup_nodes_combo_box (AnjutaPmChooserButton      *view,
						GbfProjectModel	   *model,
                  	    GtkTreePath            *root,
						GtkTreeModelFilterVisibleFunc func,
						gpointer               data,
						GtkTreeIter            *selected)
{
	GtkTreeIter iter;

	g_return_if_fail (view != NULL);
	g_return_if_fail (model != NULL);

	if ((func != NULL) || (root != NULL))
	{
		GtkTreeModel *filter;

		filter = gtk_tree_model_filter_new (GTK_TREE_MODEL (model), root);
		if (func != NULL)
		{
			gtk_tree_model_filter_set_visible_func (GTK_TREE_MODEL_FILTER (filter), func, data, NULL);
		}
		anjuta_tree_combo_box_set_model (ANJUTA_TREE_COMBO_BOX (view), filter);
		g_object_unref (filter);
		if (pm_convert_project_iter_to_model_iter (filter, &iter, selected))
		{
			anjuta_tree_combo_box_set_active_iter (ANJUTA_TREE_COMBO_BOX (view), &iter);
		}
	}
	else
    {
		anjuta_tree_combo_box_set_model (ANJUTA_TREE_COMBO_BOX (view), GTK_TREE_MODEL (model));
		if (selected)
		{
			anjuta_tree_combo_box_set_active_iter (ANJUTA_TREE_COMBO_BOX (view), selected);
		}
	}
}
