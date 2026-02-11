EditSnippetAsText()

{

    #if defined(LOGGING)
    LOGIT( _T("EditSnippetAsText[%s]"),wxT("") );
    #endif
	SnippetItemData* pSnippetItemData = (SnippetItemData*)GetItemData(GetAssociatedItemID());


    wxString editorName = GetConfig()->SettingsExternalEditor ;
    if ( editorName.IsEmpty() || (not ::wxFileExists(editorName)) )
    {
        EditSnippet( pSnippetItemData );
        return;
    }

    if ( editorName.IsEmpty() || (not ::wxFileExists(editorName)) )
    {
        #if defined(__WXMSW__)
                editorName = wxT("notepad");
        #elif defined(__UNIX__)
                editorName = wxT("vi");
        #endif
        wxString msg(wxT("Using default editor: ")+editorName+wxT("\n"));
        if (GetConfig()->IsApplication() ) msg = msg + wxT("Use Menu->");
        else msg = msg + wxT("Right click Root item. Use ");
        msg = msg + wxT("Settings to set a better editor.\n");
        GenericMessageBox( msg );
    }


    wxFileName tmpFileName = wxFileName::CreateTempFileName(wxEmptyString);

    wxFile tmpFile( tmpFileName.GetFullPath(), wxFile::write);
    if (not tmpFile.IsOpened() )
    {
        GenericMessageBox(wxT("Open failed for:")+tmpFileName.GetFullPath());
        return ;
    }
    wxString snippetData( GetSnippet() );
    tmpFile.Write( csU2C(snippetData), snippetData.Length());
    tmpFile.Close();


    wxString execString = editorName + wxT(" \"") + tmpFileName.GetFullPath() + wxT("\"");

    #ifdef LOGGING
     LOGIT( _T("Properties wxExecute[%s]"), execString.GetData() );
    #endif


    ::wxExecute( execString, wxEXEC_SYNC);

    tmpFile.Open(tmpFileName.GetFullPath(), wxFile::read);
    if (not tmpFile.IsOpened() )
    {   GenericMessageBox(wxT("Abort.Error reading temp data file."));
        return;
    }
    unsigned long fileSize = tmpFile.Length();

    #ifdef LOGGING
     LOGIT( _T("New file size[%d]"),fileSize );
    #endif


    char pBuf[fileSize+1];
    size_t nResult = tmpFile.Read( pBuf, fileSize );
    if ( wxInvalidOffset == (int)nResult )
        GenericMessageBox(wxT("Error reading temp file"));
    pBuf[fileSize] = 0;
    tmpFile.Close();

    #ifdef LOGGING

    #endif


    snippetData = csC2U( pBuf );

     #ifdef LOGGING

     #endif


    ::wxRemoveFile( tmpFileName.GetFullPath() );


    SetSnippet( snippetData );

    return;
}
