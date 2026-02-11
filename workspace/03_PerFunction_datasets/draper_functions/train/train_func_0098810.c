present (Hash *t, TObject *key)
{
  int tsize = nhash(t);
  long int h = hashindex(key);
  int h1 = h%tsize;
  TObject *rf = ref(node(t, h1));
  if (ttype(rf) != LUA_T_NIL && !luaO_equalObj(key, rf)) {
    int h2 = h%(tsize-2) + 1;
    do {
      h1 += h2;
      if (h1 >= tsize) h1 -= tsize;
      rf = ref(node(t, h1));
    } while (ttype(rf) != LUA_T_NIL && !luaO_equalObj(key, rf));
  }
  return h1;
}
