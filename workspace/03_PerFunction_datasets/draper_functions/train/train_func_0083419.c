RemoveEditor(EditorBase* eb)

{


    if (m_nRemoveEditorSentry) return;
    if (not eb) return;

    ++m_nRemoveEditorSentry;

    if (eb == m_UpdateUIFocusEditor)
        m_UpdateUIFocusEditor = 0;

    if (IsAttached() && m_InitDone) do
    {
        #if defined(LOGGING)


        #endif

        for (int i=0; i<MaxEntries; ++i )
            if ( eb == GetEditor(i)  )
                ClearEditor(i);


        if ( m_EbBrowse_MarksHash.find(eb) != m_EbBrowse_MarksHash.end())
        {
            delete m_EbBrowse_MarksHash[eb];
            m_EbBrowse_MarksHash.erase(eb);
            delete m_EdBook_MarksHash[eb];
            m_EdBook_MarksHash.erase(eb);


            if (-1 != m_pEdMgr->FindPageFromEditor(eb) )
            {
                wxWindow* win = wxWindow::FindWindowByName(wxT("SCIwindow"),eb);
                if ( win )
                {
                    win->Disconnect(wxEVT_LEFT_UP,
                                    (wxObjectEventFunction)(wxEventFunction)
                                    (wxMouseEventFunction)&BrowseTracker::OnMouseKeyEvent,
                                     NULL, this);
                    win->Disconnect(wxEVT_LEFT_DOWN,
                                    (wxObjectEventFunction)(wxEventFunction)
                                    (wxMouseEventFunction)&BrowseTracker::OnMouseKeyEvent,
                                     NULL, this);
                    win->Disconnect(wxEVT_LEFT_DCLICK,
                                    (wxObjectEventFunction)(wxEventFunction)
                                    (wxMouseEventFunction)&BrowseTracker::OnMouseKeyEvent,
                                     NULL, this);
                    win->Disconnect(wxEVT_MOTION,
                                    (wxObjectEventFunction)(wxEventFunction)
                                    (wxMouseEventFunction)&BrowseTracker::OnMouseKeyEvent,
                                     NULL, this);
                    win->Disconnect(wxEVT_CONTEXT_MENU,
                                    (wxObjectEventFunction)(wxEventFunction)
                                    (wxCommandEventFunction)&BrowseTracker::OnMarginContextMenu,
                                     NULL, this);
                }
            }
            #if defined(LOGGING)

            #endif
        }
    }while(0);

    m_nRemoveEditorSentry = 0;
}
