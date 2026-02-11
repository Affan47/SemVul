clear_unused_block_pointer_1 (tree *tp, int *, void *)
{
  if (EXPR_P (*tp) && TREE_BLOCK (*tp)
      && !TREE_USED (TREE_BLOCK (*tp)))
    TREE_SET_BLOCK (*tp, NULL);
  if (TREE_CODE (*tp) == VAR_DECL && DECL_DEBUG_EXPR_IS_FROM (*tp))
    {
      tree debug_expr = DECL_DEBUG_EXPR (*tp);
      walk_tree (&debug_expr, clear_unused_block_pointer_1, NULL, NULL);
    }
  return NULL_TREE;
}
