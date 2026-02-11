DoPrjTreeExternalDrag(wxTreeCtrl* pTree)

{
    if ( not m_prjTreeItemAtKeyDown)
        return;


    wxTextDataObject* textData = new wxTextDataObject();
    wxFileDataObject* fileData = new wxFileDataObject();

    wxString m_prjTreeText;
    if (not GetTreeSelectionData(pTree, m_prjTreeItemAtKeyDown, m_prjTreeText))
    {
        m_prjTreeText = wxEmptyString;
        return;
    }

    static const wxString delim(_T("$%["));
    if( m_prjTreeText.find_first_of(delim) != wxString::npos )
        Manager::Get()->GetMacrosManager()->ReplaceMacros(m_prjTreeText);

    wxDropSource textSource( *textData, pTree );
    textData->SetText( m_prjTreeText );

    wxDropSource fileSource( *fileData, pTree );
    wxString fileName = m_prjTreeText;

    if (not ::wxFileExists(fileName) ) fileName = wxEmptyString;

    if ( fileName.IsEmpty())
    {   if (m_prjTreeText.StartsWith(_T("http://")))
            fileName = m_prjTreeText;
        if (m_prjTreeText.StartsWith(_T("file://")))
            fileName = m_prjTreeText;

        fileName = fileName.BeforeFirst('\n');
        fileName = fileName.BeforeFirst('\r');
        if (not fileName.IsEmpty())
            textData->SetText( fileName );
    }
    fileData->AddFile( (fileName.Len() > 128) ? wxString(wxEmptyString) : fileName );


    wxDataObjectComposite* data = new wxDataObjectComposite();
    data->Add( (wxDataObjectSimple*)textData );
    data->Add( (wxDataObjectSimple*)fileData, true );


    wxDropSource source( *data, pTree  );

    #ifdef LOGGING
     LOGIT( _T("PrjTree DropSource Text[%s], File[%s]"),
                textData->GetText().c_str(),
                fileData->GetFilenames().Item(0).c_str() );
    #endif


    int flags = 0;
    flags |= wxDrag_AllowMove;

    wxDragResult result = source.DoDragDrop(flags);


    #if LOGGING
        wxString pc;
        switch ( result )
        {
            case wxDragError:   pc = _T("Error!");    break;
            case wxDragNone:    pc = _T("Nothing");   break;
            case wxDragCopy:    pc = _T("Copied");    break;
            case wxDragMove:    pc = _T("Moved");     break;
            case wxDragLink:    pc = _T("Linked");    break;
            case wxDragCancel:  pc = _T("Cancelled"); break;
            default:            pc = _T("Huh?");      break;
        }
        LOGIT( wxT("DoDragDrop returned[%s]"),pc.GetData() );
    #else
        wxUnusedVar(result);
    #endif

    delete textData;
    delete fileData;
    m_TreeText = wxEmptyString;
    #if !wxCHECK_VERSION(2, 8, 12)
    m_prjTreeItemAtKeyDown = 0;
    m_prjTreeItemAtKeyUp = 0;
    #endif


    SendMouseLeftUp(pTree, m_MouseDownX, m_MouseDownY);

}
