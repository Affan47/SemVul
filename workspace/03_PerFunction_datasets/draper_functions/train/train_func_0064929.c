dotExp(Scope *sc, Expression *e, Identifier *ident, int flag)
{   VarDeclaration *v = NULL;

#if LOGDOTEXP
    printf("Type::dotExp(e = '%s', ident = '%s')\n", e->toChars(), ident->toChars());
#endif
    Expression *ex = e;
    while (ex->op == TOKcomma)
        ex = ((CommaExp *)ex)->e2;
    if (ex->op == TOKdotvar)
    {
        DotVarExp *dv = (DotVarExp *)ex;
        v = dv->var->isVarDeclaration();
    }
    else if (ex->op == TOKvar)
    {
        VarExp *ve = (VarExp *)ex;
        v = ve->var->isVarDeclaration();
    }
    if (v)
    {
        if (ident == Id::offset)
        {
            error(e->loc, ".offset deprecated, use .offsetof");
            goto Loffset;
        }
        else if (ident == Id::offsetof)
        {
          Loffset:
            if (v->isField())
            {
                e = new IntegerExp(e->loc, v->offset, Type::tsize_t);
                return e;
            }
        }
        else if (ident == Id::init)
        {
            Type *tb = toBasetype();
            e = defaultInitLiteral(e->loc);
            if (tb->ty == Tstruct && tb->needsNested())
            {
                StructLiteralExp *se = (StructLiteralExp *)e;
                se->sinit = se->sd->toInitializer();
            }
            goto Lreturn;
        }
    }
    if (ident == Id::typeinfo)
    {
        error(e->loc, ".typeinfo deprecated, use typeid(type)");
        e = getTypeInfo(sc);
    }
    else if (ident == Id::stringof)
    {


        char *s = e->toChars();
        e = new StringExp(e->loc, s, strlen(s), 'c');
    }
    else
        e = getProperty(e->loc, ident, flag);

Lreturn:
    if (!flag || e)
        e = e->semantic(sc);
    return e;
}
