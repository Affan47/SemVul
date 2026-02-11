semantic(Scope *sc)
{
    if (!type)
    {
        UnaExp::semantic(sc);
        e1 = resolveProperties(sc, e1);
        e1 = e1->checkToBoolean(sc);
        if (e1->type == Type::terror)
            return e1;
        type = Type::tboolean;
    }
    return this;
}
