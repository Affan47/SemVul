addNamespace(const String& elementName, const Namespace& ns)
{
    ScopeMap::value_type elem(elementName, ns);
    _namespaceScopes.insert(elem);
}
