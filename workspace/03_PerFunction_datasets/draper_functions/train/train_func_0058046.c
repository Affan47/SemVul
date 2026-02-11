retreat ()
{
	if (!sync ())
		return 0;
	if (m_utfptr == m_utfbuf)
		return 0;
	do {
		m_utfptr--;
	} while ((*m_utfptr & 0xc0) == 0x80);
	return m_utfptr;
}
