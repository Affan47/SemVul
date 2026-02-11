Validate()
{
	if (m_currentSelection == -1)
		return true;

	wxString error;
	if (!ValidateFilter(error))
	{
		m_pFilterListCtrl->SetSelection(m_currentSelection);
		wxMessageBox(error, _("Filter validation failed"), wxICON_ERROR, this);
		return false;
	}

	wxString name = XRCCTRL(*this, "ID_NAME", wxTextCtrl)->GetValue();
	if (name == _T(""))
	{
		m_pFilterListCtrl->SetSelection(m_currentSelection);
		XRCCTRL(*this, "ID_NAME", wxTextCtrl)->SetFocus();
		wxMessageBox(_("Need to enter filter name"), _("Filter validation failed"), wxICON_ERROR, this);
		return false;
	}

	int pos = m_pFilterListCtrl->FindString(name);
	if (pos != wxNOT_FOUND && pos != m_currentSelection)
	{
		m_pFilterListCtrl->SetSelection(m_currentSelection);
		XRCCTRL(*this, "ID_NAME", wxTextCtrl)->SetFocus();
		wxMessageBox(_("Filter name already exists"), _("Filter validation failed"), wxICON_ERROR, this);
		return false;
	}

	return true;
}
