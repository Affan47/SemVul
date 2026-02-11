CreateSummary(wxSizer *sizer, size_t change_index)
{


	wxBoxSizer *box = new wxBoxSizer(wxVERTICAL);

	CreateSummaryGroup(box, change_index);

	sizer->Add(box, 1, wxEXPAND | wxLEFT | wxRIGHT, 5);
}
