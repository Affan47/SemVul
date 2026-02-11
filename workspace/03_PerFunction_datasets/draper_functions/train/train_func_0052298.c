getargs (char *argv[]) {
  int i;
  lua_newtable(L);
  for (i=0; argv[i]; i++) {

    lua_pushnumber(L, i);
    lua_pushstring(L, argv[i]);
    lua_settable(L, -3);
  }

  lua_pushstring(L, "n");
  lua_pushnumber(L, i-1);
  lua_settable(L, -3);
}
