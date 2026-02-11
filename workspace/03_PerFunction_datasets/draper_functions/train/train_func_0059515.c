OnRelease(bool )
{
    m_tweakmenu = 0;


    EditorManager* em = Manager::Get()->GetEditorManager();
    for (int i=0;i<em->GetEditorsCount();i++)
    {
        cbEditor* ed=em->GetBuiltinEditor(i);
        if (ed && ed->GetControl())
        {
            ed->GetControl()->Disconnect(wxEVT_NULL,(wxObjectEventFunction) (wxEventFunction) (wxCharEventFunction)&EditorTweaks::OnKeyPress);
            ed->GetControl()->Disconnect(wxEVT_NULL,(wxObjectEventFunction) (wxEventFunction) (wxCharEventFunction)&EditorTweaks::OnChar);
        }
    }

    AlignerMenuEntry e;

    ConfigManager *cfg = Manager::Get()->GetConfigManager(_T("EditorTweaks"));
    std::sort (AlignerMenuEntries.begin(), AlignerMenuEntries.end(),CompareAlignerMenuEntryObject);
    std::reverse( AlignerMenuEntries.begin(), AlignerMenuEntries.end());
    int i = 0;
    for (; i < cfg->ReadInt(_T("/aligner/max_saved_entries"),defaultStoredAlignerEntries) && i < static_cast<int>(AlignerMenuEntries.size()) ; ++i)
    {
        cfg->Write(wxString::Format(_T("/aligner/first_name_%d"),i),AlignerMenuEntries[i].MenuName);
        cfg->Write(wxString::Format(_T("/aligner/first_argument_string_%d"),i) ,AlignerMenuEntries[i].ArgumentString);

        Disconnect(AlignerMenuEntries[i].id, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(EditorTweaks::OnAlign) );
    }
    cfg->Write(_T("/aligner/saved_entries"),i);
    for (; i < static_cast<int>(AlignerMenuEntries.size()) ; ++i)
        Disconnect(AlignerMenuEntries[i].id, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(EditorTweaks::OnAlign) );
    cfg->Write(wxT("/suppress_insert_key"), m_suppress_insert);
    cfg->Write(wxT("/convert_braces"),      m_convert_braces);
}
