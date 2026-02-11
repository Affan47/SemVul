RemovePending(const CSocketEventHandler* pHandler)
{
	wxCriticalSectionLocker lock(m_sync);

	std::list<CSocketEvent*> keep;
	for (std::list<CSocketEvent*>::iterator iter = m_pending_events.begin(); iter != m_pending_events.end(); ++iter)
	{
		if ((*iter)->GetSocketEventHandler() != pHandler)
		{
			keep.push_back(*iter);
			continue;
		}

		delete *iter;
	}
	m_pending_events.swap(keep);
}
