OnLoggerDoubleClick(const wxString& file, long line)

{


    if ( GetConfig()->IsPlugin() )
    {
        EditorManager* SDKEdMgr = Manager::Get()->GetEditorManager();
        EditorBase* cbEb = 0;
        cbEditor* cbEd   = 0;
        if ( (cbEb = SDKEdMgr->IsOpen( file )) )
        {
            cbEd = SDKEdMgr->GetBuiltinEditor(cbEb);
            line -= 1;
            cbEb->Activate();


            cbEb->GotoLine(line);


            if (cbStyledTextCtrl* control = cbEd->GetControl())
            {
                control->EnsureVisible(line);

                wxFocusEvent ev(wxEVT_SET_FOCUS);
                ev.SetWindow(this);
                #if wxCHECK_VERSION(2, 9, 0)
                control->GetEventHandler()->AddPendingEvent(ev);
                #else
                control->AddPendingEvent(ev);
                #endif
            }
            return;
        }
    }


    ScbEditor* ed = GetConfig()->GetEditorManager(m_pTSFrame)->Open(file);
    if (!line || !ed)
        return;


    if (file == GetThreadSearchPlugin()->GetCodeSnippetsIndex() )
    {
        wxString currentTextLine = m_pSearchPreview->GetLine(line-1);
        currentTextLine.Trim(false);

        if ( currentTextLine.StartsWith(_T("<snippet>")) )
            currentTextLine = m_pSearchPreview->GetLine(line-2);
        CodeSnippetsEvent evt(wxEVT_CODESNIPPETS_EDIT, 0);
        evt.SetSnippetString( currentTextLine );
        evt.PostCodeSnippetsEvent(evt);
        return;
    }


    GetConfig()->GetThreadSearchPlugin()->SplitThreadSearchWindow();

    sDragScrollEvent dsEvt(wxEVT_S_DRAGSCROLL_EVENT,idDragScrollRescan);
    dsEvt.SetEventObject( GetConfig()->GetThreadSearchFrame());
    GetConfig()->GetDragScrollEvtHandler()->AddPendingEvent(dsEvt);

    line -= 1;
    ed->Activate();


    ed->GotoLine(line);


    if (cbStyledTextCtrl* control = ed->GetControl()) {
        control->EnsureVisible(line);

        wxFocusEvent ev(wxEVT_SET_FOCUS);
        ev.SetWindow(this);
        #if wxCHECK_VERSION(2, 9, 0)
        control->GetEventHandler()->AddPendingEvent(ev);
        #else
        control->AddPendingEvent(ev);
        #endif
    }
}
