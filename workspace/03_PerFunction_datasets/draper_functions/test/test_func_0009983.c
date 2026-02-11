dotExp(Scope *sc, Expression *e, Identifier *ident, int flag)
{
#if LOGDOTEXP
    printf("TypeVector::dotExp(e = '%s', ident = '%s')\n", e->toChars(), ident->toChars());
#endif
    if (ident == Id::array)
    {
        e = e->castTo(sc, basetype);
        return e;
    }
    return basetype->dotExp(sc, e->castTo(sc, basetype), ident, flag);
}
