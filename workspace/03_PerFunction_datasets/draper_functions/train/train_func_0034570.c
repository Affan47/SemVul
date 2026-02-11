OnCodeSnippetsEvent_Select(CodeSnippetsEvent& event)

{


    event.Skip();

    wxString xmlString = event.GetSnippetString();
    #if defined(LOGGING)
    int snippetID = event.GetSnippetID();
    LOGIT( _T("CodeSnippetsTreeCtrl::OnCodeSnippetsEvent_Select[%d]String[%s]"), snippetID, xmlString.c_str());
    #endif

    xmlString.Trim(false);

    int type = 0;
    long id  = 0;
    wxString idString(wxEmptyString);
    if ( xmlString.Contains(_T("type=\"category\"")))
        type = SnippetItemData::TYPE_CATEGORY;
    if ( xmlString.Contains(_T("type=\"snippet\"")))
        type = SnippetItemData::TYPE_SNIPPET;
    if ( type )
    {
        int s = xmlString.Find(_T(" ID=\""));
        if (wxNOT_FOUND == s) return;

        idString = xmlString.Mid( s+5 );
        idString = idString.Mid( 0 ,idString.Find('\"') );
        idString.ToLong(&id);
    }
    if ( id )
    {
        wxTreeItemId rootID = GetRootItem();
        wxTreeItemId treeItemID = FindTreeItemBySnippetId( id, rootID );
        if (treeItemID)
        {
            EnsureVisible( treeItemID );
            SelectItem( treeItemID );


        }
    }

}
