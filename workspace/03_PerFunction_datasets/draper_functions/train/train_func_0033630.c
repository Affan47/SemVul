e_tree_thaw_state_change (ETree *tree)
{
	g_return_if_fail (E_IS_TREE (tree));
	g_return_if_fail (tree->priv->state_change_freeze != 0);

	tree->priv->state_change_freeze--;
	if (tree->priv->state_change_freeze == 0 && tree->priv->state_changed) {
		tree->priv->state_changed = FALSE;
		e_tree_state_change (tree);
	}
}
