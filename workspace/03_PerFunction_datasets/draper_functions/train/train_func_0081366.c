gbf_project_view_remove_all_shortcut (GbfProjectView* view)
{
	GtkTreeModel* model;
	gboolean valid;
	GtkTreeIter iter;

	model = gtk_tree_view_get_model (GTK_TREE_VIEW (view));


	for (valid = gtk_tree_model_iter_children (GTK_TREE_MODEL (model), &iter, NULL);
		valid == TRUE;)
	{
		GbfTreeData *data;

		gtk_tree_model_get (GTK_TREE_MODEL (model), &iter,
		    GBF_PROJECT_MODEL_COLUMN_DATA, &data,
	    	-1);

		if (data->type == GBF_TREE_NODE_SHORTCUT)
		{
			valid = gbf_project_model_remove (GBF_PROJECT_MODEL (model), &iter);
		}
		else
		{

			break;
		}
	}
}
