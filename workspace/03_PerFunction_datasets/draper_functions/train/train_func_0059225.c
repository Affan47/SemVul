GetServerByIPUDP(uint32 nIP, uint16 nUDPPort, bool bObfuscationPorts) const
{
	for (CInternalList::const_iterator it = m_servers.begin(); it != m_servers.end(); ++it){
        CServer* const s =*it;
		if (s->GetIP() == nIP
			&& (s->GetPort() == nUDPPort-4
				|| (bObfuscationPorts && s->GetObfuscationPortUDP() == nUDPPort)
				|| s->GetPort() == nUDPPort - 12))
			return s;
	}
	return NULL;
}
