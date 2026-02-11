CopyHash(DOH *ho) {
  Hash *h, *nh;
  HashNode *n;
  DOH *nho;

  int i;
  h = (Hash *) ObjData(ho);
  nh = (Hash *) DohMalloc(sizeof(Hash));
  nh->hashsize = h->hashsize;
  nh->hashtable = (HashNode **) DohMalloc(nh->hashsize * sizeof(HashNode *));
  for (i = 0; i < nh->hashsize; i++) {
    nh->hashtable[i] = 0;
  }
  nh->nitems = 0;
  nh->line = h->line;
  nh->file = h->file;
  if (nh->file)
    Incref(nh->file);

  nho = DohObjMalloc(&DohHashType, nh);
  for (i = 0; i < h->hashsize; i++) {
    n = h->hashtable[i];
    while (n) {
      Hash_setattr(nho, n->key, n->object);
      n = n->next;
    }
  }
  return nho;
}
