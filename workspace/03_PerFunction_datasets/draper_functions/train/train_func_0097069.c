smartlist_del_keeporder(smartlist_t *sl, int idx)
{
  tor_assert(sl);
  tor_assert(idx>=0);
  tor_assert(idx < sl->num_used);
  --sl->num_used;
  if (idx < sl->num_used)
    memmove(sl->list+idx, sl->list+idx+1, sizeof(void*)*(sl->num_used-idx));
}
