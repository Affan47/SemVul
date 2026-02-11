semantic(Scope *sc)
{   Expression *e;

    if (!type)
    {   BinExp::semanticp(sc);
        e = op_overload(sc);
        if (e)
            return e;
        e1 = e1->checkIntegral();
        e2 = e2->checkIntegral();
        if (e1->type->toBasetype()->ty == Tvector ||
            e2->type->toBasetype()->ty == Tvector)
            return incompatibleTypes();
        e1 = e1->integralPromotions(sc);
        e2 = e2->castTo(sc, Type::tshiftcnt);
        type = e1->type;
    }
    return this;
}
