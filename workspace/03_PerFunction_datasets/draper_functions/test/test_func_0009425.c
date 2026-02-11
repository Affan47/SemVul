Pop()
{

	m_mutex.Lock();
	if( m_queuePos-1 < 0 )
	{
		m_queuePos = 0;
		m_dwObjectCondition |= STACK_EMPTY;
		m_mutex.Unlock();
		return FALSE;
	}
	if( m_dwObjectCondition & STACK_EMPTY )
		m_dwObjectCondition = m_dwObjectCondition ^ STACK_EMPTY;
	if( m_dwObjectCondition & STACK_OVERFLOW )
		m_dwObjectCondition = m_dwObjectCondition ^ STACK_OVERFLOW;
	if( m_dwObjectCondition & STACK_FULL )
		m_dwObjectCondition = m_dwObjectCondition ^ STACK_FULL;

	m_queuePos--;
	m_lpvProcessor = m_lppvQueue[m_queuePos];
	m_mutex.Unlock();
	return TRUE;
}
