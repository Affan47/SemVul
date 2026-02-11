AddNote(Kademlia::CEntry *pEntry)
{
	CKadEntryPtrList::iterator it = m_kadNotes.begin();
	for (; it != m_kadNotes.end(); ++it) {
		Kademlia::CEntry* entry = *it;
		if(entry->m_uIP == pEntry->m_uIP || entry->m_uSourceID == pEntry->m_uSourceID) {
			delete pEntry;
			return;
		}
	}
	m_kadNotes.push_front(pEntry);
}
