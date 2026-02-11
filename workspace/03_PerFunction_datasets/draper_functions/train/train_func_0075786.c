tinsert (lua_State *L) {
  TabA ta;
  lua_Integer e = aux_getn(L, 1, &ta) + 1;
  lua_Integer pos;
  switch (lua_gettop(L)) {
    case 2: {
      pos = e;
      break;
    }
    case 3: {
      lua_Integer i;
      pos = luaL_checkinteger(L, 2);
      luaL_argcheck(L, 1 <= pos && pos <= e, 2, "position out of bounds");
      for (i = e; i > pos; i--) {
        (*ta.geti)(L, 1, i - 1);
        (*ta.seti)(L, 1, i);
      }
      break;
    }
    default: {
      return luaL_error(L, "wrong number of arguments to 'insert'");
    }
  }
  (*ta.seti)(L, 1, pos);
  return 0;
}
