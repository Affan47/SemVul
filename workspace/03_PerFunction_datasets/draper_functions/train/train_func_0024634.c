smartlist_digest_isin(const smartlist_t *sl, const char *element)
{
  int i;
  if (!sl) return 0;
  for (i=0; i < sl->num_used; i++)
    if (tor_memeq((const char*)sl->list[i],element,DIGEST_LEN))
      return 1;
  return 0;
}
