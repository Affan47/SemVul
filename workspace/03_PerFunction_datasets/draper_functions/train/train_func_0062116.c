lj_gc_barrierf(global_State *g, GCobj *o, GCobj *v)
{
  lua_assert(isblack(o) && iswhite(v) && !isdead(g, v) && !isdead(g, o));
  lua_assert(g->gc.state != GCSfinalize && g->gc.state != GCSpause);
  lua_assert(o->gch.gct != ~LJ_TTAB);

  if (g->gc.state == GCSpropagate || g->gc.state == GCSatomic)
    gc_mark(g, v);
  else
    makewhite(g, o);
}
