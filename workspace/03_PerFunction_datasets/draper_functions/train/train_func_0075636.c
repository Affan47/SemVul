clearError()
{
	if (!m_error)
		return;

	m_error = false;
	m_errorString.clear();
	m_errorLine = 0;
}
