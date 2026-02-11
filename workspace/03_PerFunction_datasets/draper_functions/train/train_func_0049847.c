castTo(Scope *sc, Type *t)
{

    if (type->equals(t))
    {
        committed = 1;
        return this;
    }

    NullExp *e = (NullExp *)copy();
    e->committed = 1;
    Type *tb = t->toBasetype();
#if 0
    e->type = type->toBasetype();
    if (!tb->equals(e->type))
    {

        if (e->type->ty == Tpointer && e->type->nextOf()->ty == Tvoid &&
            (tb->ty == Tpointer || tb->ty == Tarray || tb->ty == Taarray ||
             tb->ty == Tdelegate))
        {
            if (tb->ty == Tdelegate)
            {   TypeDelegate *td = (TypeDelegate *)tb;
                TypeFunction *tf = (TypeFunction *)td->nextOf();

                if (!tf->varargs &&
                    !(tf->arguments && tf->arguments->dim)
                   )
                {
                    return Expression::castTo(sc, t);
                }
            }
        }
        else
        {

        }
    }
#else
    if (tb->ty == Tvoid)
    {
        e->type = type->toBasetype();
        return e->Expression::castTo(sc, t);
    }
#endif
    if (tb->ty == Tsarray || tb->ty == Tstruct)
    {
        error("cannot cast null to %s", t->toChars());
    }
    e->type = t;
    return e;
}
