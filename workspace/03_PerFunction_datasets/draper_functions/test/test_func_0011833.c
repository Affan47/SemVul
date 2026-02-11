OnCloseFrameOrWindow(wxCloseEvent &event)

{


    #if defined(LOGGING)
    LOGIT( _T("EditSnippetFrame::OnCloseFrameOrWindow"));
    #endif


    if (m_OncloseWindowEntries++)
        return;


    SaveSnippetFramePosn();
    GetConfig()->GetSnippetsTreeCtrl()->SaveDataAndCloseEditorFrame(this);


    m_OncloseWindowEntries = ((m_OncloseWindowEntries<1)? 0 : m_OncloseWindowEntries - 1);

}
