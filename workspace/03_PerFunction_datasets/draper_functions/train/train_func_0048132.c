insert_u (void *buff, int tag, stringtable *tb)
{
  TaggedString *ts;
  unsigned long h = (unsigned long)buff;
  int size = tb->size;
  int i;
  int j = -1;
  if ((long)tb->nuse*3 >= (long)size*2) {
    grow(tb);
    size = tb->size;
  }
  for (i = h%size; (ts = tb->hash[i]) != NULL; ) {
    if (ts == &EMPTY)
      j = i;
    else if (ts->constindex < 0 &&
             (tag == ts->u.d.tag || tag == LUA_ANYTAG) &&
             buff == ts->u.d.v)
      return ts;
    if (++i == size) i=0;
  }

  if (j != -1)
    i = j;
  else
    tb->nuse++;
  ts = tb->hash[i] = newone_u(buff, tag, h);
  return ts;
}
