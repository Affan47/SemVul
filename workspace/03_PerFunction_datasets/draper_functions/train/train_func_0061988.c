style_find_section_for_getting(const GtStyle *sty,
                                          const char *section)
{
  int depth = 0;
  gt_assert(sty && section);
  lua_getglobal(sty->L, "style");
  if (lua_isnil(sty->L, -1)) {
    gt_log_log("'style' is not defined");
    lua_pop(sty->L, 1);
    return -1;
  } else depth++;
  lua_getfield(sty->L, -1, section);
  if (lua_isnil(sty->L, -1) || !lua_istable(sty->L, -1)) {
    lua_pop(sty->L, 2);
    return -1;
  } else depth++;
  return depth;
}
