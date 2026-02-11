get_or_history(const char* id)
{
  or_history_t *hist;

  if (tor_digest_is_zero(id))
    return NULL;

  hist = digestmap_get(history_map, id);
  if (!hist) {
    hist = tor_malloc_zero(sizeof(or_history_t));
    rephist_total_alloc += sizeof(or_history_t);
    rephist_total_num++;
    hist->link_history_map = digestmap_new();
    hist->since = hist->changed = time(NULL);
    tor_addr_make_unspec(&hist->last_reached_addr);
    digestmap_set(history_map, id, hist);
  }
  return hist;
}
