checkIP(const UINT8 ip[4])
{
	UINT16 hashvalue=(ip[2]<<8)|ip[3];
	m_pMutex->lock();
	PTEMPIPBLOCKLIST entry = m_hashTable[hashvalue];
	PTEMPIPBLOCKLIST previous = NULL;
	while(entry) {
		if(memcmp(entry->ip,ip,2)==0) {


			UINT64 now;
			getcurrentTimeMillis(now);
			if(entry->validTimeMillis <= now) {

				if(previous==NULL) {
					m_hashTable[hashvalue] = entry->next;
				}
				else {
					previous->next = entry->next;
				}
				delete entry;
				entry = NULL;
				m_pMutex->unlock();
				return E_SUCCESS;
			}
			else {
				m_pMutex->unlock();
				return E_UNKNOWN;
			}
		}
		previous = entry;
		entry = entry->next;
	}
	m_pMutex->unlock();
	return E_SUCCESS;
}
