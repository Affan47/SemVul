vect_find_last_store_in_slp_instance (slp_instance instance)
{
  int i;
  slp_tree node;
  gimple last_store = NULL, store;

  node = SLP_INSTANCE_TREE (instance);
  for (i = 0;
       VEC_iterate (gimple, SLP_TREE_SCALAR_STMTS (node), i, store);
       i++)
    last_store = get_later_stmt (store, last_store);

  return last_store;
}
