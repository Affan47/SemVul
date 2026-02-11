semantic(Scope *sc)
{   Expression *e;

#if LOGSEMANTIC
    printf("AddExp::semantic('%s')\n", toChars());
#endif
    if (!type)
    {
        BinExp::semanticp(sc);

        e = op_overload(sc);
        if (e)
            return e;

        Type *tb1 = e1->type->toBasetype();
        Type *tb2 = e2->type->toBasetype();

        if (tb1->ty == Tdelegate ||
            tb1->ty == Tpointer && tb1->nextOf()->ty == Tfunction)
        {
            e = e1->checkArithmetic();
        }
        if (tb2->ty == Tdelegate ||
            tb2->ty == Tpointer && tb2->nextOf()->ty == Tfunction)
        {
            e = e2->checkArithmetic();
        }
        if (e)
            return e;

        if ((tb1->ty == Tarray || tb1->ty == Tsarray) &&
            (tb2->ty == Tarray || tb2->ty == Tsarray) &&
            tb1->nextOf()->equals(tb2->nextOf())
           )
        {
            type = e1->type;
            e = this;
        }
        else if (tb1->ty == Tpointer && e2->type->isintegral() ||
                 tb2->ty == Tpointer && e1->type->isintegral())
        {
            e = scaleFactor(sc);
        }
        else if (tb1->ty == Tpointer && tb2->ty == Tpointer)
        {
            return incompatibleTypes();
        }
        else
        {
            typeCombine(sc);
            Type *tb1 = e1->type->toBasetype();
            if (tb1->ty == Tvector && !tb1->isscalar())
            {
                return incompatibleTypes();
            }
            if ((tb1->isreal() && e2->type->isimaginary()) ||
                (tb1->isimaginary() && e2->type->isreal()))
            {
                switch (type->toBasetype()->ty)
                {
                    case Tfloat32:
                    case Timaginary32:
                        type = Type::tcomplex32;
                        break;

                    case Tfloat64:
                    case Timaginary64:
                        type = Type::tcomplex64;
                        break;

                    case Tfloat80:
                    case Timaginary80:
                        type = Type::tcomplex80;
                        break;

                    default:
                        assert(0);
                }
            }
            e = this;
        }
        return e;
    }
    return this;
}
