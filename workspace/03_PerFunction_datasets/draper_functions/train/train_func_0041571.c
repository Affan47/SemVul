checkEscapeRef()
{
    VarDeclaration *v = var->isVarDeclaration();
    if (v)
    {
        if (!v->isDataseg() && !(v->storage_class & (STCref | STCout)))
            error("escaping reference to local variable %s", v->toChars());
    }
}
