RemoveProjectDependency(cbProject* base, cbProject* doesNotDependOn)
{
    if (!base || !doesNotDependOn)
        return;

    DepsMap::iterator it = m_ProjectDeps.find(base);
    if (it == m_ProjectDeps.end())
        return;

    ProjectsArray* arr = it->second;
    arr->Remove(doesNotDependOn);

    Manager::Get()->GetLogManager()->DebugLog(F(_T("%s now does not depend on %s (%lu deps)"), base->GetTitle().wx_str(), doesNotDependOn->GetTitle().wx_str(), static_cast<unsigned long>(arr->GetCount())));

    if (!arr->GetCount())
    {
        m_ProjectDeps.erase(it);
        delete arr;
    }
    if (m_pWorkspace)
        m_pWorkspace->SetModified(true);
}
