operator==(const CServerPath &op) const
{
	if (m_bEmpty != op.m_bEmpty)
		return false;
	else if (m_type != op.m_type)
		return false;
	else if (m_data != op.m_data)
		return false;

	return true;
}
