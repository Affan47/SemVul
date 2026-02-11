insert_u (void *buff, int tag, stringtable *tb) {
  TaggedString *ts;
  unsigned long h = (unsigned long)buff;
  int size = tb->size;
  int j = -1;
  int h1;
  if ((long)tb->nuse*3 >= (long)size*2) {
    grow(tb);
    size = tb->size;
  }
  h1 = h%size;
  while ((ts = tb->hash[h1]) != NULL) {
    if (ts == &EMPTY)
      j = h1;
    else if ((tag == ts->u.d.tag || tag == LUA_ANYTAG) && buff == ts->u.d.v)
      return ts;
    h1 += (h&(size-2)) + 1;
    if (h1 >= size) h1 -= size;
  }

  if (j != -1)
    h1 = j;
  else
    tb->nuse++;
  ts = tb->hash[h1] = newone_u(buff, tag, h);
  return ts;
}
