may_flatten_matrices (struct cgraph_node *node)
{
  tree decl;
  struct function *func;
  basic_block bb;
  gimple_stmt_iterator gsi;

  decl = node->decl;
  if (node->analyzed)
    {
      func = DECL_STRUCT_FUNCTION (decl);
      FOR_EACH_BB_FN (bb, func)
	for (gsi = gsi_start_bb (bb); !gsi_end_p (gsi); gsi_next (&gsi))
	if (!may_flatten_matrices_1 (gsi_stmt (gsi)))
	  return false;
    }
  return true;
}
