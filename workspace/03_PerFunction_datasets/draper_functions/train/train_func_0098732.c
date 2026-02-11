singlestep (lua_State *L) {
  global_State *g = G(L);

  switch (g->gcstate) {
    case GCSpause: {
      markroot(L);
      return 0;
    }
    case GCSpropagate: {
      if (g->gray)
        return propagatemark(g);
      else {
        atomic(L);
        return 0;
      }
    }
    case GCSsweepstring: {
      lu_mem old = g->totalbytes;
      sweepwholelist(L, &g->strt.hash[g->sweepstrgc++]);
      if (g->sweepstrgc >= g->strt.size)
        g->gcstate = GCSsweep;
      lua_assert(old >= g->totalbytes);
      g->estimate -= old - g->totalbytes;
      return GCSWEEPCOST;
    }
    case GCSsweep: {
      lu_mem old = g->totalbytes;
      g->sweepgc = sweeplist(L, g->sweepgc, GCSWEEPMAX);
      if (*g->sweepgc == NULL) {
        checkSizes(L);
        g->gcstate = GCSfinalize;
      }
      lua_assert(old >= g->totalbytes);
      g->estimate -= old - g->totalbytes;
      return GCSWEEPMAX*GCSWEEPCOST;
    }
    case GCSfinalize: {
      if (g->tmudata) {
        GCTM(L);
        if (g->estimate > GCFINALIZECOST)
          g->estimate -= GCFINALIZECOST;
        return GCFINALIZECOST;
      }
      else {
        g->gcstate = GCSpause;
        g->gcdept = 0;
        return 0;
      }
    }
    default: lua_assert(0); return 0;
  }
}
