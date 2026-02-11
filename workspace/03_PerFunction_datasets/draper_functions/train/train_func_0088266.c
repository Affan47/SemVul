End() const
{
	return m_useDefault ? m_itListCurrent == m_itListEnd : m_itMapCurrent == m_itMapEnd;
}
