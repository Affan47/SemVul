GetChangeTime(CTimeEx& time, const CServer &server, const CServerPath &path)
{
	tServerIter sit = GetServerEntry(server);
	if (sit == m_serverList.end())
		return false;

	tCacheIter iter;
	bool unused;
	if (Lookup(iter, sit, path, true, unused))
	{
		time = iter->modificationTime;
		return true;
	}

	return false;
}
