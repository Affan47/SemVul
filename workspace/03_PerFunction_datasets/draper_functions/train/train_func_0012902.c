On1WayReset(wxCommandEvent &event)
{
	int item = GetSelectedDevice();
	if( item == -1 )
		return;


	int side = GetAuthoritativeSide(item);
	if( side == -1 )
		return;


	if( !ZapConflicts(item, side) )
		return;


	RewriteConfig(item);


	RefillList();


	wxMessageBox(_W("1-Way Reset is complete, and ready to sync."),
		_W("Reset Complete"), wxOK | wxICON_INFORMATION, m_parent);
}
