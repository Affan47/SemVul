size(Loc loc)
{

    if (loc.linnum == 0)
        loc = this->loc;
    if (sizeok != SIZEOKdone && scope)
        semantic(NULL);

    StructDeclaration *sd = isStructDeclaration();
    if (sizeok != SIZEOKdone && sd && sd->members)
    {


        struct SV
        {


            static int func(Dsymbol *s, void *param)
            {   SV *psv = (SV *)param;
                VarDeclaration *v = s->isVarDeclaration();
                if (v)
                {
                    if (v->scope)
                        v->semantic(NULL);
                    if (v->storage_class & (STCstatic | STCextern | STCtls | STCgshared | STCmanifest | STCctfe | STCtemplateparameter))
                        return 0;
                    if (v->isField() && v->sem >= SemanticDone)
                        return 0;
                    return 1;
                }
                return 0;
            }
        };
        SV sv;

        for (size_t i = 0; i < members->dim; i++)
        {   Dsymbol *s = (*members)[i];
            if (s->apply(&SV::func, &sv))
                goto L1;
        }
        sd->finalizeSize(NULL);

      L1: ;
    }

    if (!members)
    {
        error(loc, "unknown size");
    }
    else if (sizeok != SIZEOKdone)
    {
        error(loc, "no size yet for forward reference");

    }
    return structsize;
}
