OnCheck(wxCommandEvent& event)
	{
		if (!event.GetSelection() && !event.IsChecked())
		{
			wxCheckListBox* pListBox = XRCCTRL(*this, "ID_ACTIVE", wxCheckListBox);
			pListBox->Check(0);
			wxMessageBox(_("The filename column can neither be hidden nor moved."), _("Column properties"));
		}
	}
