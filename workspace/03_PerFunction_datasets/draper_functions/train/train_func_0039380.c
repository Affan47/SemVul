layout_lua_new(lua_State *L)
{
  GtLayout **layout;
  GtDiagram **diagram;
  unsigned int width;
  GtStyle *style;
  GtError *err;
  diagram = check_diagram(L, 1);
  width = luaL_checkint(L, 2);

  style = gt_lua_get_style_from_registry(L);
  layout = lua_newuserdata(L, sizeof (GtLayout*));
  gt_assert(layout);
  err = gt_error_new();
  *layout = gt_layout_new(*diagram, width, style, err);
  if (gt_error_is_set(err))
    return gt_lua_error(L, err);
  gt_error_delete(err);
  luaL_getmetatable(L, LAYOUT_METATABLE);
  lua_setmetatable(L, -2);
  return 1;
}
