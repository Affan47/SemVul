ht_expand (hash_table *table)
{
  hashnode *nentries, *p, *limit;
  unsigned int size, sizemask;

  size = table->nslots * 2;
  nentries = xcalloc (size, sizeof (hashnode));
  sizemask = size - 1;

  p = table->entries;
  limit = p + table->nslots;
  do
    if (*p)
      {
	unsigned int index, hash, hash2;

	hash = (*p)->hash_value;
	index = hash & sizemask;

	if (nentries[index])
	  {
	    hash2 = ((hash * 17) & sizemask) | 1;
	    do
	      {
		index = (index + hash2) & sizemask;
	      }
	    while (nentries[index]);
	  }
	nentries[index] = *p;
      }
  while (++p < limit);

  free (table->entries);
  table->entries = nentries;
  table->nslots = size;
}
