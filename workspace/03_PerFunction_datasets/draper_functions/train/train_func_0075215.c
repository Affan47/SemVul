hover_on (ETree *tree,
          gint x,
          gint y)
{
	tree->priv->hover_x = x;
	tree->priv->hover_y = y;
	if (tree->priv->hover_idle_id != 0)
		g_source_remove (tree->priv->hover_idle_id);
	tree->priv->hover_idle_id = g_timeout_add (500, hover_timeout, tree);
}
