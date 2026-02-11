inline_init_test_initialization (void **entry, void *x)
{
  struct treetreehash_entry *ite = (struct treetreehash_entry *) *entry;
  splay_tree decl_map = (splay_tree)x;

  tree h = java_treetreehash_find
    (DECL_FUNCTION_INIT_TEST_TABLE (current_function_decl), ite->key);
  if (! h)
    return true;
  splay_tree_insert (decl_map,
		     (splay_tree_key) ite->value,
		     (splay_tree_value) h);
  return true;
}
