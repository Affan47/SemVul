templateParameterLookup(Type *tparam, TemplateParameters *parameters)
{
    if (tparam->ty == Tident)
    {
        TypeIdentifier *tident = (TypeIdentifier *)tparam;

        return templateIdentifierLookup(tident->ident, parameters);
    }
    return IDX_NOTFOUND;
}
