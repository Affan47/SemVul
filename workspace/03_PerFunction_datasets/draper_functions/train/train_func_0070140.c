OnDown(wxCommandEvent& event)
	{
		wxCheckListBox* pListBox = XRCCTRL(*this, "ID_ACTIVE", wxCheckListBox);
		int sel = pListBox->GetSelection();
		if (sel < 1)
			return;
		if (sel >= (int)pListBox->GetCount() - 1)
			return;

		int tmp;
		tmp = m_order[sel + 1];
		m_order[sel + 1] = m_order[sel];
		m_order[sel] = tmp;

		wxString name = pListBox->GetString(sel);
		bool checked = pListBox->IsChecked(sel);
		pListBox->Delete(sel);
		pListBox->Insert(name, sel + 1);
		pListBox->Check(sel + 1, checked);
		pListBox->SetSelection(sel + 1);

		wxCommandEvent evt;
		OnSelChanged(evt);
	}
