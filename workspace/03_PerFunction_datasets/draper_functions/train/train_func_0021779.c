TryLockCache(enum locking_reason reason, const CServerPath& directory)
{
	wxASSERT(m_pCurrentServer);
	wxASSERT(m_pCurOpData);

	std::list<t_lockInfo>::iterator own = GetLockStatus();
	if (own == m_lockInfoList.end())
	{
		t_lockInfo info;
		info.directory = directory;
		info.pControlSocket = this;
		info.waiting = true;
		info.reason = reason;
		info.lockcount = 0;
		m_lockInfoList.push_back(info);
		own = --m_lockInfoList.end();
	}
	else
	{
		if (own->lockcount)
		{
			if (!m_pCurOpData->holdsLock)
			{
				m_pCurOpData->holdsLock = true;
				own->lockcount++;
			}
			return true;
		}
		wxASSERT(own->waiting);
		wxASSERT(own->reason == reason);
	}


	m_pCurOpData->holdsLock = true;


	for (std::list<t_lockInfo>::const_iterator iter = m_lockInfoList.begin(); iter != own; ++iter)
	{
		if (*m_pCurrentServer != *iter->pControlSocket->m_pCurrentServer)
			continue;
		if (directory != iter->directory)
			continue;
		if (reason != iter->reason)
			continue;


		return false;
	}

	own->lockcount++;
	own->waiting = false;
	return true;
}
