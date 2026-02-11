RemoveDownloadingSource(CUpDownClient* client)
{
	CClientRefList::iterator it =
		std::find(m_downloadingSourcesList.begin(), m_downloadingSourcesList.end(), CCLIENTREF(client, wxEmptyString));
	if (it != m_downloadingSourcesList.end()) {
		m_downloadingSourcesList.erase(it);
	}
}
