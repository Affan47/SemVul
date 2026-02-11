TopoSort(XOTclClass *cl, XOTclClass *base, XOTclClasses* (*next)(XOTclClass*)) {

  XOTclClasses *sl = next == Super ? cl->super : cl->sub;
  XOTclClasses *pl;


  cl->color = GRAY;
  for (; sl; sl = sl->next) {
    XOTclClass *sc = sl->cl;
    if (sc->color == GRAY) { cl->color = WHITE; return 0; }
    if (sc->color == WHITE && !TopoSort(sc, base, next)) {
      cl->color = WHITE;
      if (cl == base) {
        register XOTclClasses *pc;
        for (pc = cl->order; pc; pc = pc->next) { pc->cl->color = WHITE; }
      }
      return 0;
    }
  }
  cl->color = BLACK;
  pl = NEW(XOTclClasses);
  pl->cl = cl;
  pl->next = base->order;
  base->order = pl;
  if (cl == base) {
    register XOTclClasses *pc;
    for (pc = cl->order; pc; pc = pc->next) { pc->cl->color = WHITE; }
  }
  return 1;
}
