semantic(Scope *sc)
{
    sc->noctor++;
    if (body)
        body = body->semanticScope(sc, this, this);
    sc->noctor--;
    condition = condition->semantic(sc);
    condition = resolveProperties(sc, condition);
    condition = condition->optimize(WANTvalue);

    condition = condition->checkToBoolean(sc);

    if (condition->op == TOKerror)
        return new ErrorStatement();

    if (body && body->isErrorStatement())
        return body;

    return this;
}
