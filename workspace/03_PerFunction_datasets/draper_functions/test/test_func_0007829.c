CloseDialog()

{
	m_selectedItem = m_listBox->GetSelection();

	if ((m_selectedItem > -1) && (m_selectedItem < MaxEntries))
	{   std::map<int, int>::iterator iter = m_indexMap.find(m_selectedItem);
        LOGIT( _T("ListBox[%ld] Map[%d]"), m_selectedItem, iter->second );


        m_pBrowseTracker->m_UpdateUIEditorIndex = iter->second;
	}

	EndModal( wxID_OK );
}
