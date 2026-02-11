equals(RootObject *o)
{
    if (this == o)
        return true;
    Dsymbol *s = (Dsymbol *)(o);

    if (s && ident && s->ident && ident->equals(s->ident))
        return true;
    return false;
}
