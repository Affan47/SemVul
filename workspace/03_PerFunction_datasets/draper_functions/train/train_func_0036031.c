mark_referenced (tree id)
{
  if (!TREE_SYMBOL_REFERENCED (id))
    {
      struct cgraph_node *node;
      struct cgraph_varpool_node *vnode;

      if (!cgraph_global_info_ready)
	{
	  node = cgraph_node_for_identifier (id);
	  if (node)
	    cgraph_mark_needed_node (node);
	}

      vnode = cgraph_varpool_node_for_identifier (id);
      if (vnode)
	cgraph_varpool_mark_needed_node (vnode);
    }
  TREE_SYMBOL_REFERENCED (id) = 1;
}
