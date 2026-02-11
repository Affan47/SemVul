unregisterListener(UT_sint32 iListenerId)
{
	UT_return_if_fail(iListenerId >= 0);
	UT_return_if_fail(iListenerId >= 0 && iListenerId < static_cast<UT_sint32>(m_listeners.size()));
	m_listeners[iListenerId] = NULL;
}
