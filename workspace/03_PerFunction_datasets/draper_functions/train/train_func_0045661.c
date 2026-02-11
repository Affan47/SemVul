handle_nothrow_attribute (tree *node, tree ARG_UNUSED (name),
			  tree ARG_UNUSED (args), int ARG_UNUSED (flags),
			  bool * ARG_UNUSED (no_add_attrs))
{
  if (TREE_CODE (*node) == FUNCTION_DECL)
    TREE_NOTHROW (*node) = 1;
  else
    gcc_unreachable ();

  return NULL_TREE;
}
