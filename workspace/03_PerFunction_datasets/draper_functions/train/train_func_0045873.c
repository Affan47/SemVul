diagram_lua_new(lua_State *L)
{
  GtDiagram **diagram;
  GtFeatureIndex **feature_index;
  GtRange *range;
  GtError *err;
  const char *seqid;
  GtStyle *style;
  bool has_seqid;

  feature_index = check_feature_index(L, 1);

  seqid = luaL_checkstring(L, 2);
  err = gt_error_new();
  if (gt_feature_index_has_seqid(*feature_index, &has_seqid, seqid, err))
    return gt_lua_error(L, err);
  gt_error_delete(err);
  luaL_argcheck(L, has_seqid,
                2, "feature index does not contain the given sequence id");

  range = check_range(L, 3);

  style = gt_lua_get_style_from_registry(L);
  diagram = lua_newuserdata(L, sizeof (GtDiagram*));
  gt_assert(diagram);
  err = gt_error_new();
  *diagram = gt_diagram_new(*feature_index, seqid, range, style, err);
  if (gt_error_is_set(err))
    return gt_lua_error(L, err);
  gt_error_delete(err);
  luaL_getmetatable(L, DIAGRAM_METATABLE);
  lua_setmetatable(L, -2);
  return 1;
}
