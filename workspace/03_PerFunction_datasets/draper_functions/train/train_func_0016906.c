parse_table(lua_State *L, GtStr *out, int index, int level,
                       GtError *err)
{
  int GT_UNUSED rval, had_err = 0;
  gt_error_check(err);
  gt_assert(lua_istable(L, index));
  lua_pushnil(L);
  if (index < 0)
    index--;
  while (!had_err && (lua_next(L, index) != 0))
  {
    int i;
    for (i=0;i<level;i++)
      gt_str_append_cstr(out, "  ");
    rval = format_scalar(L, out, -2, true, NULL);
    gt_assert(!rval);
    gt_str_append_cstr(out, " = ");
    if (lua_istable(L, -1))
    {
      gt_str_append_cstr(out, "{\n");
      had_err = parse_table(L, out, -1, level+1, err);
      for (i=0;i<level;i++)
        gt_str_append_cstr(out, "  ");
      gt_str_append_cstr(out, "},\n");
    }
    else
    {
      had_err = format_scalar(L, out, -1, false, err);
      gt_str_append_cstr(out, ",\n");
    }
    lua_pop(L, 1);
  }
  return had_err;
}
