hasIdentityOpEquals(Scope *sc)
{
    Dsymbol *eq = search_function(this, Id::eq);
    if (eq)
    {


        Expression *er = new NullExp(loc, NULL);
        Expression *el = new IdentifierExp(loc, Id::p);
        Expressions *a = new Expressions();
        a->setDim(1);
        for (size_t i = 0; ; i++)
        {
            Type *tthis;
            if (i == 0) tthis = type;
            if (i == 1) tthis = type->constOf();
            if (i == 2) tthis = type->immutableOf();
            if (i == 3) tthis = type->sharedOf();
            if (i == 4) tthis = type->sharedConstOf();
            if (i == 5) break;
            FuncDeclaration *f = NULL;

            unsigned errors = global.startGagging();
            unsigned oldspec = global.speculativeGag;
            global.speculativeGag = global.gag;
            sc = sc->push();
            sc->speculative = true;

            for (size_t j = 0; j < 2; j++)
            {
                (*a)[0] = (j == 0 ? er : el);
                (*a)[0]->type = tthis;
                f = resolveFuncCall(loc, sc, eq, NULL, tthis, a, 1);
                if (f)
                    break;
            }

            sc = sc->pop();
            global.speculativeGag = oldspec;
            global.endGagging(errors);

            if (f)
                return f;
        }
    }
    return NULL;
}
