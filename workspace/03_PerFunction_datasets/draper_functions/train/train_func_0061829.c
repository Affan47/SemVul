visitDataMember(const DataMemberPtr& p)
{
    StringList metaData = getMetaData(p);
    validateType(p->type(), metaData, p->definitionContext()->filename(), p->line());
    validateGetSet(p, metaData, p->definitionContext()->filename(), p->line());
}
