e_tree_model_generator_get_column_type (GtkTreeModel *tree_model,
                                        gint index)
{
	ETreeModelGenerator *tree_model_generator = E_TREE_MODEL_GENERATOR (tree_model);

	g_return_val_if_fail (E_IS_TREE_MODEL_GENERATOR (tree_model), G_TYPE_INVALID);

	return gtk_tree_model_get_column_type (tree_model_generator->priv->child_model, index);
}
