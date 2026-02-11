getStructClassScope()
{   Scope *sc;

    for (sc = this; sc; sc = sc->enclosing)
    {
        AggregateDeclaration *ad;

        if (sc->scopesym)
        {
            ad = sc->scopesym->isClassDeclaration();
            if (ad)
                return ad;
            else
            {   ad = sc->scopesym->isStructDeclaration();
                if (ad)
                    return ad;
            }
        }
    }
    return NULL;
}
