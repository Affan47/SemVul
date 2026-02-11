wrap_cleanups_r (tree *tp, int *walk_subtrees, void * )
{
  tree exp = *tp;
  tree cleanup;


  if (TYPE_P (exp))
    {
      *walk_subtrees = 0;
      return NULL_TREE;
    }
  if (TREE_CODE (exp) != TARGET_EXPR)
    return NULL_TREE;

  cleanup = TARGET_EXPR_CLEANUP (exp);
  if (cleanup)
    {
      cleanup = build2 (MUST_NOT_THROW_EXPR, void_type_node, cleanup,
			NULL_TREE);
      TARGET_EXPR_CLEANUP (exp) = cleanup;
    }


  return NULL_TREE;
}
