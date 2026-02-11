FetchFileModificationTime(wxDateTime savedTime)

{
    if (savedTime != time_t(0))
    {   m_LastXmlModifiedTime = savedTime;
        return;
    }
    if (::wxFileExists(GetConfig()->SettingsSnippetsXmlPath) )
    {   wxFileName fname( GetConfig()->SettingsSnippetsXmlPath );
        m_LastXmlModifiedTime = fname.GetModificationTime();
    }
}
