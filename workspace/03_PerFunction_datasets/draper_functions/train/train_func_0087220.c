tree_find_mtab (tree_chunk_tab *ctab, int n_chunks, tree_kind *kind)
{
  tree_chunk_tab *t;
  tree_kind k = *kind;

  while ((t = find_ctab (ctab, n_chunks, k)) == NULL)
    {
      k = k->chunk_base;
      if (k == NULL)
	return NULL;
    }

  *kind = k;
  return t->mtab;
}
