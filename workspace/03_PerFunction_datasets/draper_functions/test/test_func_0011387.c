CreateServerEntry(const CServer& server)
{
	for (tServerIter iter = m_serverList.begin(); iter != m_serverList.end(); ++iter)
	{
		if (iter->server == server)
			return iter;
	}
	CServerEntry entry;
	entry.server = server;
	m_serverList.push_back(entry);

	return --m_serverList.end();
}
