UnlockCache()
{
	if (!m_pCurOpData || !m_pCurOpData->holdsLock)
		return;
	m_pCurOpData->holdsLock = false;

	std::list<t_lockInfo>::iterator iter = GetLockStatus();
	if (iter == m_lockInfoList.end())
		return;

	wxASSERT(!iter->waiting || iter->lockcount == 0);
	if (!iter->waiting)
	{
		iter->lockcount--;
		wxASSERT(iter->lockcount >= 0);
		if (iter->lockcount)
			return;
	}

	CServerPath directory = iter->directory;
	enum locking_reason reason = iter->reason;

	m_lockInfoList.erase(iter);


	if (!m_pCurrentServer)
	{
		LogMessage(Debug_Warning, _T("UnlockCache called with !m_pCurrentServer"));
		return;
	}
	for (std::list<t_lockInfo>::const_iterator iter = m_lockInfoList.begin(); iter != m_lockInfoList.end(); ++iter)
	{
		if (!iter->pControlSocket->m_pCurrentServer)
		{
			LogMessage(Debug_Warning, _T("UnlockCache found other instance with !m_pCurrentServer"));
			continue;
		}

		if (*m_pCurrentServer != *iter->pControlSocket->m_pCurrentServer)
			continue;

		if (iter->directory != directory)
			continue;

		if (iter->reason != reason)
			continue;


		wxCommandEvent evt(fzOBTAINLOCK);
		iter->pControlSocket->AddPendingEvent(evt);
		break;
	}
}
