gc_shrink(global_State *g, lua_State *L)
{
  if (g->strnum <= (g->strmask >> 2) && g->strmask > LJ_MIN_STRTAB*2-1)
    lj_str_resize(L, g->strmask >> 1);
  if (g->tmpbuf.sz > LJ_MIN_SBUF*2)
    lj_str_resizebuf(L, &g->tmpbuf, g->tmpbuf.sz >> 1);
}
