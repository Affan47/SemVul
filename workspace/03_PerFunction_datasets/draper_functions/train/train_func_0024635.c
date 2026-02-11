airHeapFromArray(const airArray *key, const airArray *data) {
  airHeap *h;
  unsigned int i;
  if (key==NULL || (data!=NULL && data->len!=key->len))
    return NULL;
  h = airHeapNew((data==NULL)?0:data->unit, key->incr);
  if (heapLenIncr (h, key->len)) {
    airHeapNix(h);
    return NULL;
  }
  memcpy(h->key, key->data, key->len*sizeof(double));
  if (h->data_a!=NULL) memcpy(h->data, data->data, data->len*data->unit);
  for (i=0; i<key->len; i++) {
    h->idx[i]=i;
    h->invidx[i]=i;
  }
  heapify(h);
  return h;
}
