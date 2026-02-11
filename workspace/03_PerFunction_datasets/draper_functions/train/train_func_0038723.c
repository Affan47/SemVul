giggle_rev_list_view_set_model (GiggleRevListView *list,
				GtkTreeModel      *model)
{
	GiggleRevListViewPriv *priv;
	GType                   type;

	g_return_if_fail (GIGGLE_IS_REV_LIST_VIEW (list));
	g_return_if_fail (!model || GTK_IS_TREE_MODEL (model));

	if (model) {

		type = gtk_tree_model_get_column_type (model, COL_OBJECT);
		g_return_if_fail (type == GIGGLE_TYPE_REVISION);
	}

	priv = GET_PRIV (list);

	if (model) {
		giggle_graph_renderer_validate_model
			(GIGGLE_GRAPH_RENDERER (priv->graph_renderer),
			 model, COL_OBJECT);
	}

	gtk_tree_view_set_model (GTK_TREE_VIEW (list), model);
}
