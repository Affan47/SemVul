lto_streamer_cache_delete (struct lto_streamer_cache_d *c)
{
  if (c == NULL)
    return;

  htab_delete (c->node_map);
  free_alloc_pool (c->node_map_entries);
  VEC_free (tree, heap, c->nodes);
  VEC_free (unsigned, heap, c->offsets);
  free (c);
}
