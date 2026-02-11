SetLabel(int id, const wxString& label, unsigned long maxLength )
{
	wxStaticText* pText = wxDynamicCast(FindWindow(id), wxStaticText);
	if (!pText)
		return false;

	if (!maxLength)
		pText->SetLabel(label);
	else
	{
		wxString wrapped = label;
		WrapText(this, wrapped, maxLength);
		pText->SetLabel(wrapped);
	}

	return true;
}
