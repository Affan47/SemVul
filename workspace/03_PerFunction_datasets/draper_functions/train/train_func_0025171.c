luaS_collectudata (void)
{
  TaggedString *frees = NULL;
  int i;
  L->rootglobal.next = NULL;
  for (i=0; i<NUM_HASHS; i++) {
    stringtable *tb = &L->string_root[i];
    int j;
    for (j=0; j<tb->size; j++) {
      TaggedString *t = tb->hash[j];
      if (t == NULL || t == &EMPTY || t->constindex != -1)
        continue;
      t->head.next = (GCnode *)frees;
      frees = t;
      tb->hash[j] = &EMPTY;
    }
  }
  return frees;
}
