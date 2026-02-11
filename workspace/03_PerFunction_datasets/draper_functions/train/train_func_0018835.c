handle_sentinel_attribute (tree *node, tree name, tree args,
			   int ARG_UNUSED (flags), bool *no_add_attrs)
{
  if (!prototype_p (*node))
    {
      warning (OPT_Wattributes,
	       "%qE attribute requires prototypes with named arguments", name);
      *no_add_attrs = true;
    }
  else
    {
      if (!stdarg_p (*node))
	{
	  warning (OPT_Wattributes,
		   "%qE attribute only applies to variadic functions", name);
	  *no_add_attrs = true;
	}
    }

  if (args)
    {
      tree position = TREE_VALUE (args);

      if (TREE_CODE (position) != INTEGER_CST)
	{
	  warning (OPT_Wattributes,
		   "requested position is not an integer constant");
	  *no_add_attrs = true;
	}
      else
	{
	  if (tree_int_cst_lt (position, integer_zero_node))
	    {
	      warning (OPT_Wattributes,
		       "requested position is less than zero");
	      *no_add_attrs = true;
	    }
	}
    }

  return NULL_TREE;
}
