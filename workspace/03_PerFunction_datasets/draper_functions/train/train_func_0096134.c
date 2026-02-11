giggle_view_file_set_model (GiggleViewFile *view_history,
			       GtkTreeModel   *model)
{
	GiggleViewFilePriv *priv;

	g_return_if_fail (GIGGLE_IS_VIEW_FILE (view_history));
	g_return_if_fail (GTK_IS_TREE_MODEL (model));

	priv = GET_PRIV (view_history);

	giggle_rev_list_view_set_model (GIGGLE_REV_LIST_VIEW (priv->revision_list), model);
}
