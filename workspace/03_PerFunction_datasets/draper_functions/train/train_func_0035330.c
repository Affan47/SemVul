DoItemSelectionChanged()
{
	m_ItemSelectionChangePending = false;
	CKnownFileVector filesVector;
	filesVector.reserve(GetSelectedItemCount());

	long index = GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );

	while ( index > -1 ) {
		CPartFile* file = ((FileCtrlItem_Struct*)GetItemData( index ))->GetFile();
		if (file->IsPartFile()) {
			filesVector.push_back(file);
		}
		index = GetNextItem( index, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
	}

	std::sort(filesVector.begin(), filesVector.end());
	theApp->amuledlg->m_transferwnd->clientlistctrl->ShowSources(filesVector);
}
