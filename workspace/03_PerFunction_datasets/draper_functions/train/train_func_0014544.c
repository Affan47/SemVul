lua_sethook(lua_State *L, lua_Hook func, int mask, int count)
{
  global_State *g = G(L);
  mask &= HOOK_EVENTMASK;
  if (func == NULL || mask == 0) { mask = 0; func = NULL; }
  g->hookf = func;
  g->hookcount = g->hookcstart = (int32_t)count;
  g->hookmask = (uint8_t)((g->hookmask & ~HOOK_EVENTMASK) | mask);
  lj_trace_abort(g);
  lj_dispatch_update(g);
  return 1;
}
