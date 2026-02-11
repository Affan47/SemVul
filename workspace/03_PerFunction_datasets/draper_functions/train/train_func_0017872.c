OnRemove(wxCommandEvent& event)
{
	wxListCtrl* pListCtrl = XRCCTRL(*this, "ID_EXTENSIONS", wxListCtrl);
	wxASSERT(pListCtrl);

	int item = -1;
	item = pListCtrl->GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	while (item != -1)
	{
		pListCtrl->DeleteItem(item);
		item = pListCtrl->GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	}
	SetCtrlState();
}
