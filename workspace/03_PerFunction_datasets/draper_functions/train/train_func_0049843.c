free_or_history(void *_hist)
{
  or_history_t *hist = _hist;
  digestmap_free(hist->link_history_map, _free_link_history);
  rephist_total_alloc -= sizeof(or_history_t);
  rephist_total_num--;
  tor_free(hist);
}
