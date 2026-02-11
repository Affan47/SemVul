count_functions (tree t)
{
  int i;
  if (TREE_CODE (t) == FUNCTION_DECL)
    return 1;
  else if (TREE_CODE (t) == OVERLOAD)
    {
      for (i = 0; t; t = OVL_CHAIN (t))
	i++;
      return i;
    }

  abort ();
  return 0;
}
