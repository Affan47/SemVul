scaleFactor(Scope *sc)
{
    d_uns64 stride;
    Type *t1b = e1->type->toBasetype();
    Type *t2b = e2->type->toBasetype();
    Expression *eoff;

    if (t1b->ty == Tpointer && t2b->isintegral())
    {

        Type *t = Type::tptrdiff_t;

        stride = t1b->nextOf()->size(loc);
        if (!t->equals(t2b))
            e2 = e2->castTo(sc, t);
        eoff = e2;
        e2 = new MulExp(loc, e2, new IntegerExp(Loc(), stride, t));
        e2->type = t;
        type = e1->type;
    }
    else if (t2b->ty == Tpointer && t1b->isintegral())
    {

        Type *t = Type::tptrdiff_t;
        Expression *e;

        stride = t2b->nextOf()->size(loc);
        if (!t->equals(t1b))
            e = e1->castTo(sc, t);
        else
            e = e1;
        eoff = e;
        e = new MulExp(loc, e, new IntegerExp(Loc(), stride, t));
        e->type = t;
        type = e2->type;
        e1 = e2;
        e2 = e;
    }
    else
        assert(0);

    if (sc->func && !sc->intypeof)
    {
        eoff = eoff->optimize(WANTvalue);
        if (eoff->op == TOKint64 && eoff->toInteger() == 0)
            ;
        else if (sc->func->setUnsafe())
        {
            error("pointer arithmetic not allowed in @safe functions");
            return new ErrorExp();
        }
    }

    return this;
}
