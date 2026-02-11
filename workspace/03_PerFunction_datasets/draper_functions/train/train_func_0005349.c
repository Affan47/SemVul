push_captures (MatchState *ms, const char *s, const char *e) {
  int i;
  luaL_checkstack(ms->L, ms->level, "too many captures");
  if (ms->level == 0 && s) {
    lua_pushlstring(ms->L, s, e-s);
    return 1;
  }
  else {
    for (i=0; i<ms->level; i++)
      push_onecapture(ms, i);
    return ms->level;
  }
}
