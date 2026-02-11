upheap(airHeap *h, unsigned int i) {
  while (i) {
    unsigned int parent = (i-1)/2;
    if (h->key[h->idx[parent]] > h->key[h->idx[i]]) {
      unsigned int tmp = h->idx[parent];
      h->idx[parent] = h->idx[i];
      h->idx[i] = tmp;
      h->invidx[h->idx[i]] = i;
      h->invidx[h->idx[parent]] = parent;
      i = parent;
    } else
      i = 0;
  }
}
