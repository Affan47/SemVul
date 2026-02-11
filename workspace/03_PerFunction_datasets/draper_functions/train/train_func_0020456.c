GetDependenciesForProject(cbProject* base)
{
    DepsMap::iterator it = m_ProjectDeps.find(base);
    if (it != m_ProjectDeps.end())
        return it->second;
    return nullptr;
}
