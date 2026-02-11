NewNode(DOH *k, void *obj) {
  HashNode *hn = (HashNode *) DohMalloc(sizeof(HashNode));
  hn->key = k;
  Incref(hn->key);
  hn->object = obj;
  Incref(obj);
  hn->next = 0;
  return hn;
}
