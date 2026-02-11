GetServerByIP(uint32 nIP) const
{
	for (CInternalList::const_iterator it = m_servers.begin(); it != m_servers.end(); ++it){
        CServer* const s = *it;
		if (s->GetIP() == nIP)
			return s;
	}
	return NULL;
}
