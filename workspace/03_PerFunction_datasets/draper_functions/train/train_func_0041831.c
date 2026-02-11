OnPopupGetUrl( wxCommandEvent& WXUNUSED(event) )
{
	wxString URIs;

	long index = GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );

	while (index != -1) {
		CSearchFile* file = (CSearchFile*)GetItemData( index );

		URIs += theApp->CreateED2kLink( file ) + wxT("\n");

		index = GetNextItem( index, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
	}

	if (!URIs.IsEmpty()) {
		theApp->CopyTextToClipboard( URIs.RemoveLast() );
	}
}
