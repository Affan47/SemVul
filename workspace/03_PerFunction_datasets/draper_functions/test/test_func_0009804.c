DeletePage(int nPage)
{
	wxCHECK_MSG((nPage >= 0) && (nPage < (int)GetPageCount()), false,
		wxT("Trying to delete invalid page-index in CMuleNotebook::DeletePage"));


	wxNotebookEvent evt( wxEVT_COMMAND_MULENOTEBOOK_PAGE_CLOSING, GetId(), nPage );
	evt.SetEventObject(this);
	ProcessEvent( evt );


	bool result = wxNotebook::DeletePage( nPage );


	if ( GetPageCount() && (int)GetSelection() >= (int)GetPageCount() ) {
		SetSelection( GetPageCount() - 1 );
	}


	if (GetPageCount()) {

		size_t page = nPage;

		if (page == GetPageCount()) {
			page--;
		}
		wxNotebookEvent event( wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED, GetId(), page );
		event.SetEventObject(this);
		ProcessEvent( event );
	} else {

		wxNotebookEvent event( wxEVT_COMMAND_MULENOTEBOOK_ALL_PAGES_CLOSED, GetId() );
		event.SetEventObject(this);
		ProcessEvent( event );
	}

	return result;
}
