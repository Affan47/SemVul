getdebt (global_State *g) {
  l_mem debt = g->GCdebt;
  int stepmul = g->gcstepmul;
  debt = (debt / STEPMULADJ) + 1;
  debt = (debt < MAX_LMEM / stepmul) ? debt * stepmul : MAX_LMEM;
  return debt;
}
