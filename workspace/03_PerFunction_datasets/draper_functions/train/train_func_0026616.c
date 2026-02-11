getValue(Expression *e)
{
    if (e && e->op == TOKvar)
    {
        VarDeclaration *v = ((VarExp *)e)->var->isVarDeclaration();
        if (v && v->storage_class & STCmanifest)
        {
            e = v->getConstInitializer();
        }
    }
    return e;
}
