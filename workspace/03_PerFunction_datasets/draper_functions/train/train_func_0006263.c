cgraph_varpool_finalize_decl (tree decl)
{
  struct cgraph_varpool_node *node = cgraph_varpool_node (decl);


  if (node->finalized)
    return;
  if (node->needed)
    {
      node->next_needed = cgraph_varpool_nodes_queue;
      cgraph_varpool_nodes_queue = node;
      notice_global_symbol (decl);
    }
  node->finalized = true;

  if (

      (TREE_PUBLIC (decl) && !DECL_COMDAT (decl))


      || (DECL_ASSEMBLER_NAME_SET_P (decl)
	  && TREE_SYMBOL_REFERENCED (DECL_ASSEMBLER_NAME (decl))))
    {
      cgraph_varpool_mark_needed_node (node);
    }
}
