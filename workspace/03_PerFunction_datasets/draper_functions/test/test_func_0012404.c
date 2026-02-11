set_properties()
{

	SetTitle(_W("Memo"));
	text_ctrl_2->SetMinSize(wxSize(300, -1));
	text_ctrl_2->SetFocus();
	text_ctrl_2->SetValidator(wxTextValidator(wxFILTER_NONE, m_strings.Add(m_rec.Title)));
	label_2->SetToolTip(_W("Comma separated"));
	text_ctrl_3->SetMinSize(wxSize(300, -1));
	text_ctrl_3->SetToolTip(_W("Comma separated list of categories (can be empty)"));
	text_ctrl_3->SetValidator(wxTextValidator(wxFILTER_NONE, m_strings.Add(m_category_list)));
	text_ctrl_1->SetMinSize(wxSize(-1, 240));
	text_ctrl_1->SetToolTip(_W("Body of memo"));
	text_ctrl_1->SetValidator(wxTextValidator(wxFILTER_NONE, m_strings.Add(m_rec.Body)));

}
