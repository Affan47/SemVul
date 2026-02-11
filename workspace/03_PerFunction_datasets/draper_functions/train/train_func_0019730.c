toLvalue(Scope *sc, Expression *e)
{
    if (isLvalue())
        return this;
    return Expression::toLvalue(sc, e);
}
