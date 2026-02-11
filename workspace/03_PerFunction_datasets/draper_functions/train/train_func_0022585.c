findScopeByName(const std::string& name) const
{
    for (std::list<Scope>::const_iterator it = scopeList.begin(); it != scopeList.end(); ++it) {
        if (it->className == name)
            return &*it;
    }
    return 0;
}
