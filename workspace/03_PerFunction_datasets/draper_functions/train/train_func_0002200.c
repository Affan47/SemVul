IsFileSnippet (wxTreeItemId treeItemId  )

{
    wxTreeItemId itemId = treeItemId;
    if ( itemId == (void*)0) itemId = GetSelection();
    if (not itemId.IsOk()) return false;
    if (not IsSnippet(itemId) ) return false;
    wxString fileName = GetSnippet(itemId).BeforeFirst('\r');
    fileName = fileName.BeforeFirst('\n');


        static const wxString delim(_T("$%["));
        if( fileName.find_first_of(delim) != wxString::npos )
            Manager::Get()->GetMacrosManager()->ReplaceMacros(fileName);


    if ( not ::wxFileExists( fileName) ) return false;
    return true;
}
