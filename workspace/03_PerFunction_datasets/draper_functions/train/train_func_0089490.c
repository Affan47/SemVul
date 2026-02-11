handle_no_split_stack_attribute (tree *node, tree name,
				 tree ARG_UNUSED (args),
				 int ARG_UNUSED (flags),
				 bool *no_add_attrs)
{
  tree decl = *node;

  if (TREE_CODE (decl) != FUNCTION_DECL)
    {
      error_at (DECL_SOURCE_LOCATION (decl),
		"%qE attribute applies only to functions", name);
      *no_add_attrs = true;
    }
  else if (DECL_INITIAL (decl))
    {
      error_at (DECL_SOURCE_LOCATION (decl),
		"can%'t set %qE attribute after definition", name);
      *no_add_attrs = true;
    }

  return NULL_TREE;
}
