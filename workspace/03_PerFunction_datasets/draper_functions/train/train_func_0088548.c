expand_builtin_bzero (exp)
     tree exp;
{
  tree arglist = TREE_OPERAND (exp, 1);
  tree dest, size, newarglist;
  rtx result;

  if (!validate_arglist (arglist, POINTER_TYPE, INTEGER_TYPE, VOID_TYPE))
    return NULL_RTX;

  dest = TREE_VALUE (arglist);
  size = TREE_VALUE (TREE_CHAIN (arglist));


  newarglist = build_tree_list (NULL_TREE, convert (sizetype, size));
  newarglist = tree_cons (NULL_TREE, integer_zero_node, newarglist);
  newarglist = tree_cons (NULL_TREE, dest, newarglist);

  TREE_OPERAND (exp, 1) = newarglist;
  result = expand_builtin_memset (exp, const0_rtx, VOIDmode);


  TREE_OPERAND (exp, 1) = arglist;

  return result;
}
