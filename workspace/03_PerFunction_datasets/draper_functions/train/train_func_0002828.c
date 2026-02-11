luaH_get (Table *t, const TValue *key) {
  switch (ttype(key)) {
    case LUA_TSHRSTR: return luaH_getstr(t, tsvalue(key));
    case LUA_TNUMINT: return luaH_getint(t, ivalue(key));
    case LUA_TNIL: return luaO_nilobject;
    case LUA_TNUMFLT: {
      lua_Integer k;
      if (numisinteger(fltvalue(key), &k))
        return luaH_getint(t, k);

    }
    default: {
      Node *n = mainposition(t, key);
      for (;;) {
        if (luaV_rawequalobj(gkey(n), key))
          return gval(n);
        else {
          int nx = gnext(n);
          if (nx == 0) break;
          n += nx;
        }
      };
      return luaO_nilobject;
    }
  }
}
