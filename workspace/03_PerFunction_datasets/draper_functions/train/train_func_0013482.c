semantic3()
{

    if (semanticRun != PASSsemantic2done)
        return;
    semanticRun = PASSsemantic3;


    Scope *sc = Scope::createGlobal(this);


    for (size_t i = 0; i < members->dim; i++)
    {   Dsymbol *s;

        s = (*members)[i];

        s->semantic3(sc);
    }

    sc = sc->pop();
    sc->pop();
    semanticRun = PASSsemantic3done;
}
