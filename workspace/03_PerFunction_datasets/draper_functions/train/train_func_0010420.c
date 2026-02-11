resize(Hash *h) {
  HashNode *n, *next, **table;
  int oldsize, newsize;
  int i, p, hv;

  if (h->nitems < 2 * h->hashsize)
    return;


  oldsize = h->hashsize;


  newsize = 2 * oldsize + 1;
  p = 3;
  while (p < (newsize >> 1)) {
    if (((newsize / p) * p) == newsize) {
      newsize += 2;
      p = 3;
      continue;
    }
    p = p + 2;
  }

  table = (HashNode **) DohMalloc(newsize * sizeof(HashNode *));
  for (i = 0; i < newsize; i++) {
    table[i] = 0;
  }


  h->hashsize = newsize;
  for (i = 0; i < oldsize; i++) {
    n = h->hashtable[i];
    while (n) {
      hv = Hashval(n->key) % newsize;
      next = n->next;
      n->next = table[hv];
      table[hv] = n;
      n = next;
    }
  }
  DohFree(h->hashtable);
  h->hashtable = table;
}
