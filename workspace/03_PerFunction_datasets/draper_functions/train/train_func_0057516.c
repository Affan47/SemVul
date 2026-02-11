limit_nodes (void)
{
  static GTree *ordered_nodes = NULL;
  static guint limit;
  displayed_nodes = 0;


  if (appdata.node_limit < 0)
    {
      displayed_nodes = g_tree_nnodes (canvas_nodes);
      return;
    }

  limit = appdata.node_limit;

  ordered_nodes = g_tree_new (traffic_compare);

  g_tree_foreach(canvas_nodes, (GTraverseFunc) add_ordered_node, ordered_nodes);
  g_tree_foreach(ordered_nodes, (GTraverseFunc) check_ordered_node,
		   &limit);
  g_tree_destroy (ordered_nodes);
  ordered_nodes = NULL;
}
