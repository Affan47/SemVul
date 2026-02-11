unpackint (lua_State *L, const char *str,
                              int islittle, int size, int issigned) {
  lua_Unsigned res = 0;
  int i;
  int limit = (size  <= SZINT) ? size : SZINT;
  for (i = limit - 1; i >= 0; i--) {
    res <<= NB;
    res |= (lua_Unsigned)(unsigned char)str[islittle ? i : size - 1 - i];
  }
  if (size < SZINT) {
    if (issigned) {
      lua_Unsigned mask = (lua_Unsigned)1 << (size*NB - 1);
      res = ((res ^ mask) - mask);
    }
  }
  else if (size > SZINT) {
    int mask = (!issigned || (lua_Integer)res >= 0) ? 0 : MC;
    for (i = limit; i < size; i++) {
      if ((unsigned char)str[islittle ? i : size - 1 - i] != mask)
        luaL_error(L, "%d-byte integer does not fit into Lua Integer", size);
    }
  }
  return (lua_Integer)res;
}
