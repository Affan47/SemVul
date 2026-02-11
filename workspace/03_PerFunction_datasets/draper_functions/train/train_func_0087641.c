unset_root_node (GdaTree *tree)
{
	GSList *list;
	for (list = tree->priv->managers; list; list = list->next) {
		GdaTreeManager *manager = GDA_TREE_MANAGER (list->data);

		_gda_tree_node_add_children (tree->priv->root, manager, NULL);
	}

	g_signal_handlers_disconnect_by_func (tree->priv->root,
					      G_CALLBACK (node_changed_cb), tree);
	g_signal_handlers_disconnect_by_func (tree->priv->root,
					      G_CALLBACK (node_inserted_cb), tree);
	g_signal_handlers_disconnect_by_func (tree->priv->root,
					      G_CALLBACK (node_has_child_toggled_cb), tree);
	g_signal_handlers_disconnect_by_func (tree->priv->root,
					      G_CALLBACK (node_deleted_cb), tree);

	g_object_unref (tree->priv->root);
}
