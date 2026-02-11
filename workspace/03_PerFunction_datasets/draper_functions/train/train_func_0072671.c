score_matrix_lua_new_read_protein(lua_State *L)
{
  GtScoreMatrix **sm;
  const char *path;
  GtError *err;
  gt_assert(L);
  path = luaL_checkstring(L, 1);
  sm = lua_newuserdata(L, sizeof (GtScoreMatrix*));
  gt_assert(sm);
  err = gt_error_new();
  if (!(*sm = gt_score_matrix_new_read_protein(path, err)))
    return gt_lua_error(L, err);
  gt_error_delete(err);
  gt_assert(*sm);
  luaL_getmetatable(L, SCOREMATRIX_METATABLE);
  lua_setmetatable(L, -2);
  return 1;
}
