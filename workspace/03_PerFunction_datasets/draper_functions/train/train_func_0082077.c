ClearHistory()
{
    while (m_list->GetCount())
        m_list->RemoveFileFromHistory(0);
    Manager::Get()->GetConfigManager(_T("app"))->DeleteSubPath(m_configPath);

    Initialize();
    RefreshStartHerePage();
}
