record_tm_replacement (tree from, tree to)
{
  struct tree_map **slot, *h;


  DECL_UNINLINABLE (from) = 1;

  if (tm_wrap_map == NULL)
    tm_wrap_map = htab_create_ggc (32, tree_map_hash, tree_map_eq, 0);

  h = ggc_alloc_tree_map ();
  h->hash = htab_hash_pointer (from);
  h->base.from = from;
  h->to = to;

  slot = (struct tree_map **)
    htab_find_slot_with_hash (tm_wrap_map, h, h->hash, INSERT);
  *slot = h;
}
