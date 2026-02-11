CreateLayout()
{
	wxSizer *topsizer = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer *msgsizer = new wxBoxSizer(wxHORIZONTAL);


	msgsizer->Add(
		new wxStaticText(this, wxID_ANY, _W("Successfully auto-detected Evolution configuration!")),
		0, wxALIGN_LEFT | wxTOP | wxLEFT | wxRIGHT, 10);

	topsizer->Add(msgsizer, 0, 0, 0);
	topsizer->Add( new wxStaticLine(this),
		0, wxTOP | wxLEFT | wxRIGHT | wxEXPAND, 10);

	wxBoxSizer *buttons = new wxBoxSizer(wxHORIZONTAL);
	buttons->Add( new wxButton(this, Dialog_EvoDefault_ManualConfigButton,
			_W("Manual Cfg...")),
		0, wxALIGN_LEFT | wxEXPAND, 0);
	buttons->AddStretchSpacer(1);

	wxButton *ok = new wxButton(this, wxID_OK, _T("Ok"));
	ok->SetDefault();
	buttons->Add( ok, 0, wxALIGN_RIGHT | wxEXPAND, 0);

	topsizer->Add(buttons, 0, wxALL | wxEXPAND | wxALIGN_RIGHT, 10);

	SetSizer(topsizer);
	topsizer->SetSizeHints(this);
	topsizer->Layout();
}
