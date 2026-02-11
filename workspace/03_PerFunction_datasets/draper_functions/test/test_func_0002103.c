Connected()
{
	if (!m_nodeSearchStarted && IsFWCheckUDPRunning()) {
		CSearchManager::FindNodeFWCheckUDP();
		m_nodeSearchStarted = true;
		m_testStart = ::GetTickCount();
		m_timedOut = false;
	}
}
