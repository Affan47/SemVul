GetTabSize(wxDC& dc, wxWindow* wnd, const wxString& caption, const wxBitmap& bitmap, bool active, int close_button_state, int* x_extent)
	{
		wxSize size = wxAuiDefaultTabArt::GetTabSize(dc, wnd, caption, bitmap, active, close_button_state, x_extent);

		wxString text = caption;
		int pos;
		if ((pos = caption.Find(_T(" ("))) != -1)
			text = text.Left(pos);
		std::map<wxString, int>::iterator iter = m_data->maxSizes.find(text);
		if (iter == m_data->maxSizes.end())
			m_data->maxSizes[text] = size.x;
		else
		{
			if (iter->second > size.x)
			{
				size.x = iter->second;
				*x_extent = size.x;
			}
			else
				iter->second = size.x;
		}

		return size;
	}
