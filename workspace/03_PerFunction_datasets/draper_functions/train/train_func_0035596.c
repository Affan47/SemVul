digestmap_free(digestmap_t *map, void (*free_val)(void*))
{
  digestmap_entry_t **ent, **next, *this;
  if (!map)
    return;
  for (ent = HT_START(digestmap_impl, &map->head); ent != NULL; ent = next) {
    this = *ent;
    next = HT_NEXT_RMV(digestmap_impl, &map->head, ent);
    if (free_val)
      free_val(this->val);
    tor_free(this);
  }
  tor_assert(HT_EMPTY(&map->head));
  HT_CLEAR(digestmap_impl, &map->head);
  tor_free(map);
}
