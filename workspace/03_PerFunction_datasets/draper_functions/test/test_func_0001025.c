semantic(Scope *sc)
{
    protection = sc->protection;

    if (scope)
    {   sc = scope;
        scope = NULL;
    }

    if (global.params.useUnitTests)
    {
        if (!type)
            type = new TypeFunction(NULL, Type::tvoid, FALSE, LINKd);
        Scope *sc2 = sc->push();
        sc2->linkage = LINKd;
        FuncDeclaration::semantic(sc2);
        sc2->pop();
    }

#if 0


    Module *m = getModule();
    if (!m)
        m = sc->module;
    if (m)
    {

        m->needmoduleinfo = 1;
    }
#endif
}
