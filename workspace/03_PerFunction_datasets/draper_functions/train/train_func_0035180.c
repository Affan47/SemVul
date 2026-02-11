OnDelete(wxCommandEvent& event)
{
	int item = m_pFilterListCtrl->GetSelection();
	if (item == -1)
		return;

	m_currentSelection = -1;
	m_pFilterListCtrl->Delete(item);
	m_filters.erase(m_filters.begin() + item);


	for (std::vector<CFilterSet>::iterator iter = m_filterSets.begin(); iter != m_filterSets.end(); ++iter)
	{
		CFilterSet& set = *iter;
		set.local.erase(set.local.begin() + item);
		set.remote.erase(set.remote.begin() + item);
	}

	ClearFilter(true);
	SetCtrlState(false);
}
