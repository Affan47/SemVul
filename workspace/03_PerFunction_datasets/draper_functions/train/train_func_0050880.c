gbf_project_model_clear (GbfProjectModel *model)
{
	GtkTreeIter child;
	gboolean valid;

	valid = gtk_tree_model_iter_children (GTK_TREE_MODEL (model), &child, NULL);
	while (valid)
	{
		valid = gbf_project_model_remove (model, &child);
	}
}
