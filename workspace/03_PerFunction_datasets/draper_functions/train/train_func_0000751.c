resolveArrayLength(Expression *e)
{
    if (e->op == TOKnull)
        return 0;
    if (e->op == TOKslice)
    {   uinteger_t ilo = ((SliceExp *)e)->lwr->toInteger();
        uinteger_t iup = ((SliceExp *)e)->upr->toInteger();
        return iup - ilo;
    }
    if (e->op == TOKstring)
    {   return ((StringExp *)e)->len;
    }
    if (e->op == TOKarrayliteral)
    {   ArrayLiteralExp *ale = (ArrayLiteralExp *)e;
        return ale->elements ? ale->elements->dim : 0;
    }
    if (e->op == TOKassocarrayliteral)
    {   AssocArrayLiteralExp *ale = (AssocArrayLiteralExp *)e;
        return ale->keys->dim;
    }
    assert(0);
    return 0;
}
