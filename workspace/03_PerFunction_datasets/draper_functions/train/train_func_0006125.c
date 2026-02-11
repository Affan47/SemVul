alloc_stmt_list (void)
{
  tree list;
  if (!VEC_empty (tree, stmt_list_cache))
    {
      list = VEC_pop (tree, stmt_list_cache);
      memset (list, 0, sizeof(struct tree_base));
      TREE_SET_CODE (list, STATEMENT_LIST);
    }
  else
    list = make_node (STATEMENT_LIST);
  TREE_TYPE (list) = void_type_node;
  return list;
}
