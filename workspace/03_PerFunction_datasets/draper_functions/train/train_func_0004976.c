mk_S(Atom* ap, Pair* pp)
{
  Sexp *sp;

  sp = (Sexp *) emalloc(sizeof(Sexp));
  if (ap){
    sp->type = 0;
    sp->u.atom = ap;
  } else if (pp){
    sp->type = 1;
    sp->u.pair = pp;
  } else {
    error("unknown material", (Sexp*) 0);
  }
  return sp;
}
