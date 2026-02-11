gt_style_load_str(GtStyle *sty, GtStr *instr, GtError *err)
{
#ifndef NDEBUG
  int stack_size;
#endif
  int had_err = 0;
  gt_error_check(err);
  gt_assert(sty && instr);
  gt_rwlock_wrlock(sty->lock);
#ifndef NDEBUG
  stack_size = lua_gettop(sty->L);;
#endif
  if (luaL_loadbuffer(sty->L, gt_str_get(instr), gt_str_length(instr), "str") ||
      lua_pcall(sty->L, 0, 0, 0)) {
    gt_error_set(err, "cannot run style buffer: %s",
              lua_tostring(sty->L, -1));
    had_err = -1;
    lua_pop(sty->L, 1);
  }
  gt_assert(lua_gettop(sty->L) == stack_size);
  gt_rwlock_unlock(sty->lock);
  return had_err;
}
