Validate()
{
	if (!XRCCTRL(*this, "ID_PROXYTYPE_NONE", wxRadioButton)->GetValue())
	{
		wxTextCtrl* pTextCtrl = XRCCTRL(*this, "ID_PROXY_HOST", wxTextCtrl);
		if (pTextCtrl->GetValue() == _T(""))
			return DisplayError(_T("ID_PROXY_HOST"), _("You need to enter a proxy host."));
	}

	if (XRCCTRL(*this, "ID_PROXYTYPE_CUSTOM", wxRadioButton)->GetValue())
	{
		wxTextCtrl* pTextCtrl = XRCCTRL(*this, "ID_LOGINSEQUENCE", wxTextCtrl);
		if (pTextCtrl->GetValue() == _T(""))
			return DisplayError(_T("ID_LOGINSEQUENCE"), _("The custom login sequence cannot be empty."));
	}

	return true;
}
