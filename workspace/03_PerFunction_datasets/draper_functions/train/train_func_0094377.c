resolve(Loc loc, Scope *sc, Expression **pe, Type **pt, Dsymbol **ps, bool intypeid)
{
    *pe = NULL;
    *pt = NULL;
    *ps = NULL;


    if (inuse)
    {
        inuse = 2;
        error(loc, "circular typeof definition");
        goto Lerr;
    }
    inuse++;

    Type *t;
    {
        Scope *sc2 = sc->push();
        sc2->intypeof = 1;
        sc2->speculative = true;
        sc2->flags |= sc->flags & SCOPEstaticif;
        unsigned oldspecgag = global.speculativeGag;
        if (global.gag)
            global.speculativeGag = global.gag;
        exp = exp->semantic(sc2);
#if DMDV2
        exp = resolvePropertiesOnly(sc2, exp);
#endif
        global.speculativeGag = oldspecgag;
        sc2->pop();
        if (exp->op == TOKtype)
        {
            error(loc, "argument %s to typeof is not an expression", exp->toChars());
            goto Lerr;
        }
        t = exp->type;
        if (!t)
        {
            error(loc, "expression (%s) has no type", exp->toChars());
            goto Lerr;
        }
        if (t->ty == Ttypeof)
        {
            error(loc, "forward reference to %s", toChars());
            goto Lerr;
        }
    }
    if (idents.dim == 0)
        *pt = t;
    else
    {
        if (Dsymbol *s = t->toDsymbol(sc))
            resolveHelper(loc, sc, s, NULL, pe, pt, ps, intypeid);
        else
        {
            Expression *e = new TypeExp(loc, t);
            for (size_t i = 0; i < idents.dim; i++)
            {
                RootObject *id = idents[i];
                switch (id->dyncast())
                {
                    case DYNCAST_IDENTIFIER:
                        e = new DotIdExp(loc, e, (Identifier *)id);
                        break;
                    case DYNCAST_DSYMBOL:
                    {
                        TemplateInstance *ti = ((Dsymbol *)id)->isTemplateInstance();
                        e = new DotExp(loc, e, new ScopeExp(loc, ti));
                        break;
                    }
                    default:
                        assert(0);
                }
            }
            e = e->semantic(sc);
            if ((*ps = getDsymbol(e)) == NULL)
            {
                if (e->op == TOKtype)
                    *pt = e->type;
                else
                    *pe = e;
            }
        }
    }
    if (*pt)
        (*pt) = (*pt)->addMod(mod);
    inuse--;
    return;

Lerr:
    *pt = Type::terror;
    inuse--;
    return;
}
