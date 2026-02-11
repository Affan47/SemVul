OnClose(wxCloseEvent &event)

{

    if (m_bOnActivateBusy)
        return;

    if ( GetConfig()->GetDragScrollPlugin() )
    {
        CodeBlocksEvent cbEvent;
        GetConfig()->GetDragScrollPlugin()->OnStartShutdown( cbEvent);
        GetConfig()->GetDragScrollPlugin()->OnRelease(true);
    }


    if (GetSnippetsWindow())
            if ( GetSnippetsWindow()->GetFileChanged() )
                GetSnippetsWindow()->GetSnippetsTreeCtrl()->SaveItemsToFile(GetConfig()->SettingsSnippetsXmlPath);


    GetConfig()->GetSnippetsWindow()->OnClose(event);


    GetConfig()->m_appIsShutdown = true;

    RemoveKeepAliveFile();

    TerminateRecentFilesHistory();


    if ( 0 == GetConfig()->GetKeepAlivePid() )
    if ( Manager::Get() )
    {

        if (wxFileExists(m_ConfigFolder+_T("/default.conf.backup")) )
            wxRemoveFile(m_ConfigFolder+_T("/default.conf.backup")) ;
        if (wxFileExists(m_ConfigFolder+_T("/default.conf.cbTemp")) )
            wxRemoveFile(m_ConfigFolder+_T("/default.conf.cbTemp")) ;
    }

    Destroy();
}
