resolve(Loc loc, Scope *sc, Expression **pe, Type **pt, Dsymbol **ps, bool intypeid)
{


    Dsymbol *s;

    *pe = NULL;
    *pt = NULL;
    *ps = NULL;

#if 0
    if (!idents.dim)
    {
        error(loc, "template instance '%s' has no identifier", toChars());
        return;
    }
#endif


    s = tempinst;
    if (s)
    {

        s->semantic(sc);
    }
    resolveHelper(loc, sc, s, NULL, pe, pt, ps, intypeid);
    if (*pt)
        *pt = (*pt)->addMod(mod);

}
