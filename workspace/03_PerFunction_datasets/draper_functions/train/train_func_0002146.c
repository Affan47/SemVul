AddMapping(wxSizer *sizer,
				XmlNodeMapping &mapping,
				bool differing)
{


	wxFont priority_font = GetFont();
	priority_font.SetWeight( wxFONTWEIGHT_BOLD );


	wxFont priority_changed = priority_font;
	priority_changed.SetStyle( wxFONTSTYLE_ITALIC );

	wxFont changed = GetFont();
	changed.SetStyle( wxFONTSTYLE_ITALIC );

	for( size_t i = 0; i < mapping.size(); i++ ) {
		wxString data(mapping[i].Summary().raw().c_str(), wxConvUTF8);

		wxStaticText *text = new wxStaticText(this, wxID_ANY, data,
				wxDefaultPosition, wxDefaultSize,
				wxALIGN_CENTRE | wxST_NO_AUTORESIZE);
		if( mapping.Priority() == 0 ) {
			if( differing )
				text->SetFont(priority_changed);
			else
				text->SetFont(priority_font);
		}
		else {
			if( differing )
				text->SetFont(changed);
		}
		text->Wrap(m_max_text_width);

		sizer->Add( text, 0, wxEXPAND, 0);
	}
}
