semantic3(Scope *sc)
{

    if (members)
    {
        StructDeclaration *sd = isStructDeclaration();
        if (!sc)
            goto Lxop;

        sc = sc->push(this);
        sc->parent = this;
        for (size_t i = 0; i < members->dim; i++)
        {
            Dsymbol *s = (*members)[i];
            s->semantic3(sc);
        }
        sc = sc->pop();

        if (!getRTInfo && Type::rtinfo &&
            (!isDeprecated() || global.params.useDeprecated) &&
            (type && type->ty != Terror))
        {

            Objects *tiargs = new Objects();
            tiargs->push(type);
            TemplateInstance *ti = new TemplateInstance(loc, Type::rtinfo, tiargs);
            ti->semantic(sc);
            ti->semantic2(sc);
            ti->semantic3(sc);
            Dsymbol *s = ti->toAlias();
            Expression *e = new DsymbolExp(Loc(), s, 0);

            Scope *sc2 = ti->tempdecl->scope->startCTFE();
            sc2->instantiatingModule = sc->instantiatingModule ? sc->instantiatingModule : sc->module;
            e = e->semantic(sc2);
            sc2->endCTFE();

            e = e->ctfeInterpret();
            getRTInfo = e;
        }

        if (sd)
        {
        Lxop:
            if (sd->xeq &&
                sd->xeq->scope &&
                sd->xeq->semanticRun < PASSsemantic3done)
            {
                unsigned errors = global.startGagging();
                sd->xeq->semantic3(sd->xeq->scope);
                if (global.endGagging(errors))
                    sd->xeq = sd->xerreq;
            }

            if (sd->xcmp &&
                sd->xcmp->scope &&
                sd->xcmp->semanticRun < PASSsemantic3done)
            {
                unsigned errors = global.startGagging();
                sd->xcmp->semantic3(sd->xcmp->scope);
                if (global.endGagging(errors))
                    sd->xcmp = sd->xerrcmp;
            }

            FuncDeclaration *ftostr = search_toString(sd);
            if (ftostr &&
                ftostr->scope &&
                ftostr->semanticRun < PASSsemantic3done)
            {
                ftostr->semantic3(ftostr->scope);
            }

            FuncDeclaration *ftohash = search_toHash(sd);
            if (ftohash &&
                ftohash->scope &&
                ftohash->semanticRun < PASSsemantic3done)
            {
                ftohash->semantic3(ftohash->scope);
            }
        }
    }
}
