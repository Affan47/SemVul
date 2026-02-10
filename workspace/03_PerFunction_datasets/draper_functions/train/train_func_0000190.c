gda_tree_node_get_parent (GdaTreeNode *node)
{
	GdaTreeNode *parent;
	g_return_val_if_fail (GDA_IS_TREE_NODE (node), NULL);
	parent = node->priv->parent;

	if (parent && !parent->priv->parent)
		return NULL;
	else
		return parent;
}
