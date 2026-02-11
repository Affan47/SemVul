GetReplyCode() const
{
	if (m_Response == _T(""))
		return 0;

	if (m_Response[0] < '0' || m_Response[0] > '9')
		return 0;

	return m_Response[0] - '0';
}
