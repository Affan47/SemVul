clutter_path_get_node (ClutterPath     *path,
                       guint            index_,
                       ClutterPathNode *node)
{
  ClutterPathNodeFull *node_full;
  ClutterPathPrivate *priv;

  g_return_if_fail (CLUTTER_IS_PATH (path));

  priv = path->priv;

  node_full = g_slist_nth_data (priv->nodes, index_);

  g_return_if_fail (node_full != NULL);

  *node = node_full->k;
}
