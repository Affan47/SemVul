IsClientRequestPending(const CPartFile* pForFile, uint16 nPart)
{
	for (CAICHRequestedDataList::iterator it = m_liRequestedData.begin();it != m_liRequestedData.end(); ++it) {
		if (it->m_pPartFile == pForFile && it->m_nPart == nPart) {
			return true;
		}
	}
	return false;
}
