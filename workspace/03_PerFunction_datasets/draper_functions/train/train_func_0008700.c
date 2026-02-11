arrayExpressionToCommonType(Scope *sc, Expressions *exps, Type **pt)
{
#if DMDV1


    Type *t0 = NULL;
    for (size_t i = 0; i < exps->dim; i++)
    {   Expression *e = (*exps)[i];

        if (!e->type)
        {   error("%s has no value", e->toChars());
            e = new ErrorExp();
        }
        e = resolveProperties(sc, e);

        if (!t0)
            t0 = e->type;
        else
            e = e->implicitCastTo(sc, t0);
        (*exps)[i] = e;
    }

    if (!t0)
        t0 = Type::tvoid;
    if (pt)
        *pt = t0;


    return exps;
#endif
#if DMDV2


    IntegerExp integerexp(0);
    CondExp condexp(Loc(), &integerexp, NULL, NULL);

    Type *t0 = NULL;
    Expression *e0;
    size_t j0;
    for (size_t i = 0; i < exps->dim; i++)
    {
        Expression *e = (*exps)[i];
        e = resolveProperties(sc, e);
        if (!e->type)
        {
            e->error("%s has no value", e->toChars());
            e = new ErrorExp();
        }

        if (Expression *ex = e->isTemp())
            e = ex;
        e = e->isLvalue() ? callCpCtor(sc, e) : valueNoDtor(e);

        if (t0)
        {
            if (t0 != e->type)
            {


                condexp.type = NULL;
                condexp.e1 = e0;
                condexp.e2 = e;
                condexp.loc = e->loc;
                condexp.semantic(sc);
                (*exps)[j0] = condexp.e1;
                e = condexp.e2;
                j0 = i;
                e0 = e;
                t0 = e0->type;
            }
        }
        else
        {
            j0 = i;
            e0 = e;
            t0 = e->type;
        }
        (*exps)[i] = e;
    }

    if (t0)
    {
        for (size_t i = 0; i < exps->dim; i++)
        {   Expression *e = (*exps)[i];
            e = e->implicitCastTo(sc, t0);
            (*exps)[i] = e;
        }
    }
    else
        t0 = Type::tvoid;
    if (pt)
        *pt = t0;


    return exps;
#endif
}
