unload_project (GbfProjectModel *model)
{
	if (model->priv->proj) {
		gtk_tree_row_reference_free (model->priv->root);
		model->priv->root = NULL;

		gbf_project_model_clear (model);

		g_list_free (model->priv->shortcuts);
		model->priv->shortcuts = NULL;


		model->priv->proj = NULL;

		insert_empty_node (model);
	}
}
