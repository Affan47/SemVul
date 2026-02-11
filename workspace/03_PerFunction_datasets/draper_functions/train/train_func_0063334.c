assoc_remove_quoted_nulls (h)
     HASH_TABLE *h;
{
  int i;
  BUCKET_CONTENTS *tlist;
  char *t;

  if (h == 0 || assoc_empty (h))
    return ((HASH_TABLE *)NULL);

  for (i = 0; i < h->nbuckets; i++)
    for (tlist = hash_items (i, h); tlist; tlist = tlist->next)
      {
	t = remove_quoted_nulls ((char *)tlist->data);
	tlist->data = t;
      }

  return h;
}
