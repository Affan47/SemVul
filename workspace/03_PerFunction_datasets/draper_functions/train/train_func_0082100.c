searchUFCS(Scope *sc, UnaExp *ue, Identifier *ident)
{
    Loc loc = ue->loc;
    Dsymbol *s = NULL;

    for (Scope *scx = sc; scx; scx = scx->enclosing)
    {
        if (!scx->scopesym)
            continue;
        s = scx->scopesym->search(loc, ident, 0);
        if (s)
        {

            if (s->isOverloadSet())
                break;

            if (AliasDeclaration *ad = s->isAliasDeclaration())
            {
                if (ad->import)
                    break;
            }

            Dsymbol *p = s->toParent2();
            if (p && p->isModule())
                break;
        }
        s = NULL;
    }
    if (!s)
        return ue->e1->type->Type::getProperty(loc, ident, 0);

    FuncDeclaration *f = s->isFuncDeclaration();
    if (f)
    {
        TemplateDeclaration *td = getFuncTemplateDecl(f);
        if (td)
        {
            if (td->overroot)
                td = td->overroot;
            s = td;
        }
    }

    if (ue->op == TOKdotti)
    {
        DotTemplateInstanceExp *dti = (DotTemplateInstanceExp *)ue;
        TemplateInstance *ti = new TemplateInstance(loc, s->ident);
        ti->tiargs = dti->ti->tiargs;
        if (!ti->updateTemplateDeclaration(sc, s))
            return new ErrorExp();
        return new ScopeExp(loc, ti);
    }
    else
    {
        return new DsymbolExp(loc, s, 1);
    }
}
