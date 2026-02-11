semantic(Scope *sc)
{
#if LOGSEMANTIC
    printf("DotIdExp::semantic(this = %p, '%s')\n", this, toChars());

#endif
    Expression *e = semanticY(sc, 1);
    if (e && isDotOpDispatch(e))
    {
        unsigned errors = global.startGagging();
        e = resolvePropertiesX(sc, e);
        if (global.endGagging(errors))
            e = NULL;
        else
            return e;
    }
    if (!e)
    {


        e = resolveUFCSProperties(sc, this);
    }
    return e;
}
