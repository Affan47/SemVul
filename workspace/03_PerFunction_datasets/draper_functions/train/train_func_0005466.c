handle_alloc_size_attribute (tree *node, tree ARG_UNUSED (name), tree args,
			     int ARG_UNUSED (flags), bool *no_add_attrs)
{
  unsigned arg_count = type_num_arguments (*node);
  for (; args; args = TREE_CHAIN (args))
    {
      tree position = TREE_VALUE (args);

      if (TREE_CODE (position) != INTEGER_CST
	  || TREE_INT_CST_HIGH (position)
	  || TREE_INT_CST_LOW (position) < 1
	  || TREE_INT_CST_LOW (position) > arg_count )
	{
	  warning (OPT_Wattributes,
	           "alloc_size parameter outside range");
	  *no_add_attrs = true;
	  return NULL_TREE;
	}
    }
  return NULL_TREE;
}
