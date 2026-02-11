trySemantic(Scope *sc)
{

    unsigned errors = global.startGagging();
    Expression *e = semantic(sc);
    if (global.endGagging(errors))
    {
        e = NULL;
    }

    return e;
}
