createObject(const std::string& name)
{
    FactoryMap::const_iterator I = m_factories.find(name);
    if (I == m_factories.end()) {
        return Root(0);
    } else {
        return (*I).second.first(name, (*I).second.second);
    }
}
