ReadShortFromFont()
{
	short snInput;

    if (m_pbLim && 2 > m_pbLim - m_pbNext)
        THROW(kresReadFault);

    snInput = (m_pbNext[0] << 8) + m_pbNext[1];
	m_pbNext += 2;
	return snInput;
}
