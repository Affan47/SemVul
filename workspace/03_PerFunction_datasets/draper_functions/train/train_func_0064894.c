toDsymbol(Scope *sc)
{
    Type *t;

    t = semantic(loc, sc);
    if (t == this)
        return NULL;
    return t->toDsymbol(sc);
}
