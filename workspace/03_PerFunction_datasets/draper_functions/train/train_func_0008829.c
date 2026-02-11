toLvalue(Scope *sc, Expression *e)
{
    if (type && type->toBasetype()->ty == Tvoid)
        error("voids have no value");
    return this;
}
