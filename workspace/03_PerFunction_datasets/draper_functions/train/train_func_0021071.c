keyindex(lua_State *L, GCtab *t, cTValue *key)
{
  TValue tmp;
  if (tvisint(key)) {
    int32_t k = intV(key);
    if ((uint32_t)k < t->asize)
      return (uint32_t)k;
    setnumV(&tmp, (lua_Number)k);
    key = &tmp;
  } else if (tvisnum(key)) {
    lua_Number nk = numV(key);
    int32_t k = lj_num2int(nk);
    if ((uint32_t)k < t->asize && nk == (lua_Number)k)
      return (uint32_t)k;
  }
  if (!tvisnil(key)) {
    Node *n = hashkey(t, key);
    do {
      if (lj_obj_equal(&n->key, key))
	return t->asize + (uint32_t)(n - noderef(t->node));

    } while ((n = nextnode(n)));
    if (key->u32.hi == 0xfffe7fff)
      return key->u32.lo - 1;
    lj_err_msg(L, LJ_ERR_NEXTIDX);
    return 0;
  }
  return ~0u;
}
