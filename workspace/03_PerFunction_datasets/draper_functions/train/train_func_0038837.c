lj_tab_get(lua_State *L, GCtab *t, cTValue *key)
{
  if (tvisstr(key)) {
    cTValue *tv = lj_tab_getstr(t, strV(key));
    if (tv)
      return tv;
  } else if (tvisint(key)) {
    cTValue *tv = lj_tab_getint(t, intV(key));
    if (tv)
      return tv;
  } else if (tvisnum(key)) {
    lua_Number nk = numV(key);
    int32_t k = lj_num2int(nk);
    if (nk == (lua_Number)k) {
      cTValue *tv = lj_tab_getint(t, k);
      if (tv)
	return tv;
    } else {
      goto genlookup;
    }
  } else if (!tvisnil(key)) {
    Node *n;
  genlookup:
    n = hashkey(t, key);
    do {
      if (lj_obj_equal(&n->key, key))
	return &n->val;
    } while ((n = nextnode(n)));
  }
  return niltv(L);
}
