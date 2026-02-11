equal(Sexp* var1, Sexp* var2)
{
  if (var1->type != 0 || var2->type != 0)
    readerror("not atom -- eqvar");

  Atom* ap1 = var1->u.atom;
  Atom* ap2 = var2->u.atom;

  if (!strcmp(ap1->u.sym, ap2->u.sym))
    return 1;
  else
    return 0;
}
