semantic(Scope *sc)
{
    if (!type)
        type = Type::tfloat64;
    else
        type = type->semantic(loc, sc);
    return this;
}
