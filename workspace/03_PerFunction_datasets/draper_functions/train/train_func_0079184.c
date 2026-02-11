GetFileLinkExt (wxTreeItemId treeItemId  )

{


    if ( not IsFileLinkSnippet(treeItemId) ) return wxT("");
    wxTreeItemId itemId = treeItemId;
    if ( itemId == (void*)0) itemId = GetSelection();
    if (not itemId.IsOk()) return wxT("");
    if (not IsSnippet(itemId) ) return wxT("");
    wxString fileName = GetSnippet(itemId).BeforeFirst('\r');
    fileName = fileName.BeforeFirst('\n');


        static const wxString delim(_T("$%["));
        if( fileName.find_first_of(delim) != wxString::npos )
            Manager::Get()->GetMacrosManager()->ReplaceMacros(fileName);


    if ( not ::wxFileExists( fileName) ) return wxT("");
    wxFileName filename(fileName);
    return filename.GetExt();
}
