FindOpenFilesListWindow()

{

    wxFrame* pFrame = Manager::Get()->GetAppFrame();
    int idMenuOpenFilesList = ::wxFindMenuItemId( pFrame, wxT("View"), wxT("Open files list"));
    #if defined(__WXGTK__)
      idMenuOpenFilesList = ::wxFindMenuItemId( pFrame, wxT("View"), wxT("_Open files list"));
    #endif
    int idWindowOpenFilesList = 0;
    if (idMenuOpenFilesList != wxNOT_FOUND)
    {
        #if defined(LOGGING)
        LOGIT( _T("idMenuOpenFilesList:[%d]"), idMenuOpenFilesList );
        #endif


        idWindowOpenFilesList = idMenuOpenFilesList - 1;
        wxWindow* pOpenFilesListWin = wxWindow::FindWindowById( idWindowOpenFilesList, pFrame);
        if (pOpenFilesListWin)
        {
            #if defined(LOGGING)
            LOGIT( _T("pOpenFilesListWin[%p] name[%s] label[%s]"), pOpenFilesListWin,
                pOpenFilesListWin->GetName().c_str(),
                pOpenFilesListWin->GetLabel().c_str()
                );
            #endif
            return pOpenFilesListWin;
        }
    }
    return 0;
}
