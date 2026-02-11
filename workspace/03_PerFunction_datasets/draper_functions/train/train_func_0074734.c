addk (FuncState *fs, TValue *key, TValue *v) {
  lua_State *L = fs->ls->L;
  TValue *idx = luaH_set(L, fs->h, key);
  Proto *f = fs->f;
  int k, oldsize;
  if (ttisnumber(idx)) {
    lua_Number n = nvalue(idx);
    lua_number2int(k, n);
    if (luaV_rawequalobj(&f->k[k], v))
      return k;


  }

  oldsize = f->sizek;
  k = fs->nk;


  setnvalue(idx, cast_num(k));
  luaM_growvector(L, f->k, k, f->sizek, TValue, MAXARG_Ax, "constants");
  while (oldsize < f->sizek) setnilvalue(&f->k[oldsize++]);
  setobj(L, &f->k[k], v);
  fs->nk++;
  luaC_barrier(L, f, v);
  return k;
}
