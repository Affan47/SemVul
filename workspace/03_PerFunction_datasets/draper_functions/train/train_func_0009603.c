SetListColumns()

{
	m_pListLog->ClearAll();


    ConfigManager* pCfg = Manager::Get()->GetConfigManager(_T("SnippetsSearch"));
    int directoryColSize  = pCfg->ReadInt(wxT("/LogColSizeDir"), 100);
    int fileColSize  = pCfg->ReadInt(wxT("/LogColSizeFile"), 100);
    int lineColSize  = pCfg->ReadInt(wxT("/LogColSizeLine"),  50);
    int textColSize  = pCfg->ReadInt(wxT("/LogColSizeText"), 500);

	m_pListLog->InsertColumn(0, wxT("Directory"), wxLIST_FORMAT_LEFT, directoryColSize);
	m_pListLog->InsertColumn(1, wxT("File"),      wxLIST_FORMAT_LEFT, fileColSize);
	m_pListLog->InsertColumn(2, wxT("Line"),      wxLIST_FORMAT_RIGHT, lineColSize);
	m_pListLog->InsertColumn(3, wxT("Text"),      wxLIST_FORMAT_LEFT, textColSize);
}
