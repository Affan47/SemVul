cp_check_const_attributes (tree attributes)
{
  tree attr;
  for (attr = attributes; attr; attr = TREE_CHAIN (attr))
    {
      tree arg;
      for (arg = TREE_VALUE (attr); arg; arg = TREE_CHAIN (arg))
	{
	  tree expr = TREE_VALUE (arg);
	  if (EXPR_P (expr))
	    TREE_VALUE (arg) = maybe_constant_value (expr);
	}
    }
}
