OnShowDetails(wxCommandEvent &event)
{
	if( m_status_edit->IsShown() ) {
		m_status_edit->Hide();
		m_details_button->SetLabel(_W("Show Details"));
	}
	else {
		if( !m_repositioned ) {


			wxSize size = GetSize();
			wxPoint pos = GetScreenPosition();
			int screen_height = wxSystemSettings::GetMetric(wxSYS_SCREEN_Y);
			int new_height = size.GetHeight() + 470;
			if( (pos.y + new_height) > screen_height &&
			    new_height < screen_height )
			{
				int wiggle_room = screen_height - new_height;
				int y = wiggle_room / 2;
				Move(pos.x, y);
			}

			m_repositioned = true;
		}

		m_status_edit->Show();
		m_details_button->SetLabel(_W("Hide Details"));
	}
	m_topsizer->Fit(this);
}
