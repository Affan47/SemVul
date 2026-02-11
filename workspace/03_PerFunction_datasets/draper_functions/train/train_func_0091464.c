OnMnuAddSubCategory(wxCommandEvent& event)

{

	CodeSnippetsTreeCtrl* pTree = GetSnippetsTreeCtrl();
	wxTreeItemId newItem =
        GetSnippetsTreeCtrl()->AddCategory(GetSnippetsTreeCtrl()->GetAssociatedItemID(),
                                    _("New category"),0,true);
	SetFileChanged(true);
	if (newItem.IsOk())
	{
	    pTree->SelectItem(newItem);
	    pTree->SetAssociatedItemID(newItem);
        OnMnuRename(event);
	}
	if ( (newItem.IsOk()) && (pTree->GetItemText(newItem).IsEmpty()) )
        pTree->RemoveItem(newItem);
}
