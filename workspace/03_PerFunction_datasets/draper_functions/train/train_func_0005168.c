semantic(Scope *sc, TemplateParameters *parameters)
{
    bool wasSame = (sparam->type == valType);
    sparam->semantic(sc);
    if (sparam->type == Type::terror && wasSame)
    {


        valType = Type::terror;
        return;
    }
    valType = valType->semantic(loc, sc);
    if (!(valType->isintegral() || valType->isfloating() || valType->isString()) &&
        valType->ty != Tident)
    {
        if (valType != Type::terror)
            error(loc, "arithmetic/string type expected for value-parameter, not %s", valType->toChars());
    }

#if 0
    if (specValue)
    {
        Expression *e = specValue;
        sc = sc->startCTFE();
        e = e->semantic(sc);
        sc = sc->endCTFE();
        e = e->implicitCastTo(sc, valType);
        e = e->ctfeInterpret();
        if (e->op == TOKint64 || e->op == TOKfloat64 ||
            e->op == TOKcomplex80 || e->op == TOKnull || e->op == TOKstring)
            specValue = e;

    }

    if (defaultValue)
    {
        Expression *e = defaultValue;
        sc = sc->startCTFE();
        e = e->semantic(sc);
        sc = sc->endCTFE();
        e = e->implicitCastTo(sc, valType);
        e = e->ctfeInterpret();
        if (e->op == TOKint64)
            defaultValue = e;

    }
#endif
}
