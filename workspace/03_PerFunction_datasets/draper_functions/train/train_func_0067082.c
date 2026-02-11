singlestep (lua_State *L) {
  global_State *g = G(L);
  switch (g->gcstate) {
    case GCSpause: {

      g->GCmemtrav = g->strt.size * sizeof(GCObject*);
      lua_assert(!isgenerational(g));
      restartcollection(g);
      g->gcstate = GCSpropagate;
      return g->GCmemtrav;
    }
    case GCSpropagate: {
      if (g->gray) {
        lu_mem oldtrav = g->GCmemtrav;
        propagatemark(g);
        return g->GCmemtrav - oldtrav;
      }
      else {
        lu_mem work;
        int sw;
        g->gcstate = GCSatomic;
        g->GCestimate = g->GCmemtrav;  ;
        work = atomic(L);
        g->GCestimate += work;
        sw = entersweep(L);
        return work + sw * GCSWEEPCOST;
      }
    }
    case GCSsweepstring: {
      int i;
      for (i = 0; i < GCSWEEPMAX && g->sweepstrgc + i < g->strt.size; i++)
        sweepwholelist(L, &g->strt.hash[g->sweepstrgc + i]);
      g->sweepstrgc += i;
      if (g->sweepstrgc >= g->strt.size)
        g->gcstate = GCSsweepudata;
      return i * GCSWEEPCOST;
    }
    case GCSsweepudata: {
      if (g->sweepfin) {
        g->sweepfin = sweeplist(L, g->sweepfin, GCSWEEPMAX);
        return GCSWEEPMAX*GCSWEEPCOST;
      }
      else {
        g->gcstate = GCSsweep;
        return 0;
      }
    }
    case GCSsweep: {
      if (g->sweepgc) {
        g->sweepgc = sweeplist(L, g->sweepgc, GCSWEEPMAX);
        return GCSWEEPMAX*GCSWEEPCOST;
      }
      else {

        GCObject *mt = obj2gco(g->mainthread);
        sweeplist(L, &mt, 1);
        checkSizes(L);
        g->gcstate = GCSpause;
        return GCSWEEPCOST;
      }
    }
    default: lua_assert(0); return 0;
  }
}
