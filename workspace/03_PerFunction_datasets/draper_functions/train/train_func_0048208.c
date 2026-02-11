expand_builtin_bcopy (tree arglist)
{
  tree src, dest, size, newarglist;

  if (!validate_arglist (arglist,
			 POINTER_TYPE, POINTER_TYPE, INTEGER_TYPE, VOID_TYPE))
    return NULL_RTX;

  src = TREE_VALUE (arglist);
  dest = TREE_VALUE (TREE_CHAIN (arglist));
  size = TREE_VALUE (TREE_CHAIN (TREE_CHAIN (arglist)));


  newarglist = build_tree_list (NULL_TREE, convert (sizetype, size));
  newarglist = tree_cons (NULL_TREE, src, newarglist);
  newarglist = tree_cons (NULL_TREE, dest, newarglist);

  return expand_builtin_memmove (newarglist, const0_rtx, VOIDmode);
}
