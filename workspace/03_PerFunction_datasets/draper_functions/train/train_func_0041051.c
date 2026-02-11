decl_debug_args_insert (tree from)
{
  struct tree_vec_map *h;
  void **loc;

  if (DECL_HAS_DEBUG_ARGS_P (from))
    return decl_debug_args_lookup (from);
  if (debug_args_for_decl == NULL)
    debug_args_for_decl = htab_create_ggc (64, tree_vec_map_hash,
					   tree_vec_map_eq, 0);
  h = ggc_alloc_tree_vec_map ();
  h->base.from = from;
  h->to = NULL;
  loc = htab_find_slot_with_hash (debug_args_for_decl, h, DECL_UID (from),
				  INSERT);
  *(struct tree_vec_map **) loc = h;
  DECL_HAS_DEBUG_ARGS_P (from) = 1;
  return &h->to;
}
