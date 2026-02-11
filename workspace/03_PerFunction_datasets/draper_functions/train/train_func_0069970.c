semantic(Scope *sc)
{
#if LOGSEMANTIC
    printf("DotExp::semantic('%s')\n", toChars());
    if (type) printf("\ttype = %s\n", type->toChars());
#endif
    e1 = e1->semantic(sc);
    e2 = e2->semantic(sc);
    if (e2->op == TOKimport)
    {
        ScopeExp *se = (ScopeExp *)e2;
        TemplateDeclaration *td = se->sds->isTemplateDeclaration();
        if (td)
        {   Expression *e = new DotTemplateExp(loc, e1, td);
            e = e->semantic(sc);
            return e;
        }
    }
    if (!type)
        type = e2->type;
    return this;
}
