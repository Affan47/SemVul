lua_newstate (lua_Alloc f, void *ud) {
  int i;
  lua_State *L;
  global_State *g;
  LG *l = cast(LG *, (*f)(ud, NULL, LUA_TTHREAD, sizeof(LG)));
  if (l == NULL) return NULL;
  L = &l->l.l;
  g = &l->g;
  L->next = NULL;
  L->tt = LUA_TTHREAD;
  g->currentwhite = bit2mask(WHITE0BIT, FIXEDBIT);
  L->marked = luaC_white(g);
  g->gckind = KGC_NORMAL;
  preinit_state(L, g);
  g->frealloc = f;
  g->ud = ud;
  g->mainthread = L;
  g->seed = makeseed(L);
  g->uvhead.u.l.prev = &g->uvhead;
  g->uvhead.u.l.next = &g->uvhead;
  g->gcrunning = 0;
  g->GCestimate = 0;
  g->strt.size = 0;
  g->strt.nuse = 0;
  g->strt.hash = NULL;
  setnilvalue(&g->l_registry);
  luaZ_initbuffer(L, &g->buff);
  g->panic = NULL;
  g->version = NULL;
  g->gcstate = GCSpause;
  g->allgc = NULL;
  g->finobj = NULL;
  g->tobefnz = NULL;
  g->sweepgc = g->sweepfin = NULL;
  g->gray = g->grayagain = NULL;
  g->weak = g->ephemeron = g->allweak = NULL;
  g->totalbytes = sizeof(LG);
  g->GCdebt = 0;
  g->gcpause = LUAI_GCPAUSE;
  g->gcmajorinc = LUAI_GCMAJOR;
  g->gcstepmul = LUAI_GCMUL;
  for (i=0; i < LUA_NUMTAGS; i++) g->mt[i] = NULL;
  if (luaD_rawrunprotected(L, f_luaopen, NULL) != LUA_OK) {

    close_state(L);
    L = NULL;
  }
  return L;
}
