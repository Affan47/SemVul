_gda_tree_node_get_manager_for_child (GdaTreeNode *node, GdaTreeNode *child)
{
	GSList *list;
	g_return_val_if_fail (GDA_IS_TREE_NODE (node), NULL);
	g_return_val_if_fail (GDA_IS_TREE_NODE (child), NULL);
	g_return_val_if_fail (child->priv->parent == node, NULL);

	for (list = node->priv->children; list; list = list->next)
		if (g_slist_find (GDA_TREE_NODES_LIST (list->data)->nodes, child))
			return GDA_TREE_NODES_LIST (list->data)->mgr;

	return NULL;
}
