writeMessageToLogFile(const Message& msg)
{
	CMT3LOG("L3: writeMessageToLogFile\n");
	CMT3EXITLOG;

	if (!m_logFile.isOpen())
		return m_lastResult = XRV_NOFILEOPEN;

	return m_lastResult = m_logFile.writeMessage(&msg);
}
