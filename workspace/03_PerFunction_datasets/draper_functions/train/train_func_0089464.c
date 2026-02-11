OnCheck(wxCommandEvent& event)
{
	if (event.GetId() == XRCID("ID_CHECKBETA"))
	{
		if (event.IsChecked())
		{
			if (wxMessageBox(_("Do you really want to check for beta versions?\nUnless you want to test new features, keep using stable versions."), _("Update wizard"), wxICON_QUESTION | wxYES_NO, this) != wxYES)
			{
				XRCCTRL(*this, "ID_CHECKBETA", wxCheckBox)->SetValue(0);
				return;
			}
			COptions::Get()->SetOption(OPTION_UPDATECHECK_CHECKBETA, 1);
		}
		else
			COptions::Get()->SetOption(OPTION_UPDATECHECK_CHECKBETA, 0);

	}
	else if (event.GetId() == XRCID("ID_CHECKNIGHTLY") && event.IsChecked())
	{
		if (wxMessageBox(_("Warning, use nightly builds at your own risk.\nNo support is given for nightly builds.\nNightly builds may not work as expected and might even damage your system.\n\nDo you really want to check for nightly builds?"), _("Update wizard"), wxICON_EXCLAMATION | wxYES_NO, this) != wxYES)
		{
			XRCCTRL(*this, "ID_CHECKNIGHTLY", wxCheckBox)->SetValue(0);
			return;
		}
	}
}
