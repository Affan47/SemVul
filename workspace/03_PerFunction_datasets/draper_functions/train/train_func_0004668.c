handle_externally_visible_attribute (tree *pnode, tree name,
				     tree ARG_UNUSED (args),
				     int ARG_UNUSED (flags),
				     bool *no_add_attrs)
{
  tree node = *pnode;

  if (TREE_CODE (node) == FUNCTION_DECL || TREE_CODE (node) == VAR_DECL)
    {
      if ((!TREE_STATIC (node) && TREE_CODE (node) != FUNCTION_DECL
	   && !DECL_EXTERNAL (node)) || !TREE_PUBLIC (node))
	{
	  warning (OPT_Wattributes,
		   "%qE attribute have effect only on public objects", name);
	  *no_add_attrs = true;
	}
    }
  else
    {
      warning (OPT_Wattributes, "%qE attribute ignored", name);
      *no_add_attrs = true;
    }

  return NULL_TREE;
}
