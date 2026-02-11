reliesOnTident(TemplateParameters *tparams)
{
    if (tparams)
    {
        for (size_t i = 0; i < tparams->dim; i++)
        {
            TemplateParameter *tp = (*tparams)[i];
            if (tempinst->name == tp->ident)
                return this;
        }
        if (!tempinst->tiargs)
            return NULL;
        for (size_t i = 0; i < tempinst->tiargs->dim; i++)
        {
            Type *t = isType((*tempinst->tiargs)[i]);
            t = t ? t->reliesOnTident(tparams) : NULL;
            if (t)
                return t;
        }
        return NULL;
    }
    else
    {
        return Type::reliesOnTident(tparams);
    }
}
