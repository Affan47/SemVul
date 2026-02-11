OnRemoveFriend(wxCommandEvent& WXUNUSED(event))
{
	wxString question;
	if (GetSelectedItemCount() == 1) {
		question = _("Are you sure that you wish to delete the selected friend?");
	} else {
		question = _("Are you sure that you wish to delete the selected friends?");
	}

	if ( wxMessageBox( question, _("Cancel"), wxICON_QUESTION | wxYES_NO, this) == wxYES ) {
		long index = GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );

		while( index != -1 ) {
			CFriend* cur_friend = (CFriend*)GetItemData(index);
			theApp->friendlist->RemoveFriend(cur_friend);

			index = GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
		}
	}
}
