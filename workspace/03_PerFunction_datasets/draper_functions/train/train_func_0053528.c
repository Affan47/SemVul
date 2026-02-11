Main_AddDestSizer(wxSizer *sizer)
{
	wxArrayString devices;
	devices.Add(_W("Prompt to plug in later..."));
	for( Barry::Probe::Results::const_iterator i = m_results.begin();
				i != m_results.end(); ++i )
	{
		devices.Add(wxString(i->GetDisplayName().c_str(), wxConvUTF8));
	}

	wxSizer *dest = new wxStaticBoxSizer(
		new wxStaticBox(this, wxID_ANY, _W("Destination device")),
		wxVERTICAL
		);
	dest->Add(
		m_dest_combo = new wxChoice(this, wxID_ANY,
			wxDefaultPosition, wxSize(225, -1), devices),
		0, wxALL, 5);
	m_dest_combo->SetSelection(0);


	wxArrayString write_modes;


	write_modes.Add(_W("Erase all, then restore"));
	write_modes.Add(_W("Add new, and overwrite existing"));
	write_modes.Add(_W("Add only, don't overwrite existing"));
	write_modes.Add(_W("Add every record as a new entry (may cause duplicates)"));

	dest->Add( new wxStaticText(this, wxID_ANY, _W("Write Mode:")),
		0, wxTOP | wxLEFT | wxRIGHT, 5);
	dest->Add( m_write_mode_combo = new wxChoice(this, wxID_ANY,
			wxDefaultPosition, wxSize(225, -1), write_modes),
		0, wxALL, 5);
	m_write_mode_combo->SetSelection(0);


	sizer->Add(dest, 0, wxEXPAND, 0);
}
