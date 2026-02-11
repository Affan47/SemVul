gda_tree_update_part (GdaTree *tree, GdaTreeNode *node, GError **error)
{
	GSList *mgrlist;
	GdaTreeManager *mgr;
	GdaTreeNode *top;

	g_return_val_if_fail (GDA_IS_TREE (tree), FALSE);
	g_return_val_if_fail (GDA_IS_TREE_NODE (node), FALSE);

	top = gda_tree_node_get_parent (node);
	if (!top)
		top = tree->priv->root;
	mgr = _gda_tree_node_get_manager_for_child (top, node);
	mgrlist = (GSList*) gda_tree_manager_get_managers (mgr);

	if (mgrlist) {
		gboolean res;
		res = create_or_update_children (mgrlist, node, FALSE, error);
		return res;
	}
	return TRUE;
}
