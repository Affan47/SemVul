OnMnuCopy(wxCommandEvent& event)

{

    SetActiveMenuId( event.GetId() );
    if (pTiXmlDoc) { delete pTiXmlDoc; pTiXmlDoc = 0;}
    pTiXmlDoc = GetSnippetsTreeCtrl()->CopyTreeNodeToXmlDoc( GetAssociatedItemID() );
}
