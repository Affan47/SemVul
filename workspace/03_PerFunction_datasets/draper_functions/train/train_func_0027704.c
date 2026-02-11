Read(const wxString& key, wxString* str)
{
    if (m_namespace.empty())
        return false;
    ConfigManager *c = Manager::Get()->GetConfigManager(m_namespace);
    return c->Read(key, str);
}
