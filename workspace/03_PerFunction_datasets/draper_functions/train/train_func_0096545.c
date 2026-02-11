insert (char *str, stringtable *tb)
{
  TaggedString *ts;
  unsigned long h = hash(str);
  int i;
  int j = -1;
  if ((Long)tb->nuse*3 >= (Long)tb->size*2)
  {
    if (!initialized)
      initialize();
    grow(tb);
  }
  i = h%tb->size;
  while (tb->hash[i])
  {
    if (tb->hash[i] == &EMPTY)
      j = i;
    else if (strcmp(str, tb->hash[i]->str) == 0)
      return tb->hash[i];
    i = (i+1)%tb->size;
  }

  lua_pack();
  if (j != -1)
    i = j;
  else
    tb->nuse++;
  ts = tb->hash[i] = (TaggedString *)luaI_malloc(sizeof(TaggedString)+strlen(str));
  strcpy(ts->str, str);
  ts->marked = 0;
  ts->hash = h;
  ts->varindex = ts->constindex = NOT_USED;
  return ts;
}
