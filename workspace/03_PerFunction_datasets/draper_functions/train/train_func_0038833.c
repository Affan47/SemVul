castTo(Scope *sc, Type *t)
{
    if (type->equals(t))
        return this;

    TupleExp *e = (TupleExp *)copy();
    e->e0 = e0 ? e0->copy() : NULL;
    e->exps = (Expressions *)exps->copy();
    for (size_t i = 0; i < e->exps->dim; i++)
    {   Expression *ex = (*e->exps)[i];
        ex = ex->castTo(sc, t);
        (*e->exps)[i] = ex;
    }
    return e;
}
