gt_lua_get_table_as_strarray(lua_State *L, int index, GtStrArray *outarray,
                                 GtError *err)
{
  int had_err = 0;
  gt_assert(lua_istable(L, index));
  lua_pushnil(L);
  while (!had_err && (lua_next(L, index) != 0))
  {
    if (!lua_isstring(L, -1)) {
      had_err = -1;
      gt_error_set(err, "table contains non-string value!");
      break;
    }
    gt_str_array_add_cstr(outarray, lua_tostring(L, -1));
    lua_pop(L, 1);
  }
  return 0;
}
