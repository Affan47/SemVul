removedyncap (lua_State *L, Capture *capture,
                         int level, int last) {
  int id = finddyncap(capture + level, capture + last);
  int top = lua_gettop(L);
  if (id == 0) return 0;
  lua_settop(L, id - 1);
  return top - id + 1;
}
