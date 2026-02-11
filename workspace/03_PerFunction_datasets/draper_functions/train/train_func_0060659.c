lua_strcollector (void)
{
  Long counter = 0;
  int i;
  for (i=0; i<NUM_HASHS; i++)
  {
    stringtable *tb = &string_root[i];
    int j;
    for (j=0; j<tb->size; j++)
    {
      TaggedString *t = tb->hash[j];
      if (t != NULL && t->marked <= 1)
      {
        if (t->marked)
          t->marked = 0;
        else
        {
          luaI_free(t);
          tb->hash[j] = &EMPTY;
          counter++;
        }
      }
    }
  }
  return counter;
}
