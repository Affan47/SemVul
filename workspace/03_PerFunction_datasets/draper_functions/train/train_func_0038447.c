OnItemSelectionChanged(wxListEvent& evt)
{
	EClientShow clientShowMode = (EClientShow) m_radioClientMode->GetSelection();


	if ( clientShowMode == ClientShowSelected ) {
		SelectionUpdated();
	}

	evt.Skip();
}
