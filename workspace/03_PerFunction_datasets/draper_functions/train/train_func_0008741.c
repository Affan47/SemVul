checkPurity(Scope *sc, VarDeclaration *v)
{


    if (sc->func &&
        !sc->intypeof &&
        !(sc->flags & SCOPEdebug) &&
        v->ident != Id::ctfe &&
        !v->isImmutable() &&
        !(v->isConst() && !v->isRef() && (v->isDataseg() || v->isParameter()) &&
          v->type->implicitConvTo(v->type->immutableOf())) &&

        !(v->storage_class & STCmanifest)
       )
    {
        if (v->isDataseg())
        {


            bool msg = FALSE;
            for (Dsymbol *s = sc->func; s; s = s->toParent2())
            {
                FuncDeclaration *ff = s->isFuncDeclaration();
                if (!ff)
                    break;

                if (ff->setImpure() && !msg && strcmp(v->ident->toChars(), "__gate"))
                {   error("pure function '%s' cannot access mutable static data '%s'",
                        sc->func->toPrettyChars(), v->toChars());
                    msg = TRUE;
                }
            }
        }
        else
        {


            if ((sc->func->ident == Id::require || sc->func->ident == Id::ensure) &&
                v->isParameter() && sc->func->parent == v->parent)
            {
                return;
            }


            Dsymbol *vparent = v->toParent2();
            for (Dsymbol *s = sc->func; s; s = s->toParent2())
            {
                if (s == vparent)
                        break;
                FuncDeclaration *ff = s->isFuncDeclaration();
                if (!ff)
                    break;
                if (ff->setImpure())
                {   error("pure nested function '%s' cannot access mutable data '%s'",
                        ff->toChars(), v->toChars());
                    break;
                }
            }
        }


        if (v->storage_class & STCgshared)
        {
            if (sc->func->setUnsafe())
                error("safe function '%s' cannot access __gshared data '%s'",
                    sc->func->toChars(), v->toChars());
        }
    }
}
