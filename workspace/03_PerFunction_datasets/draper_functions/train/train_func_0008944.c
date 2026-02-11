putW(UKWORD w)
{
	if (m_bad)
		return 0;

	m_bad = (fputc((UKBYTE)w, m_file) == EOF);
	if (m_bad)
	  return 0;
	m_bad = (fputc((UKBYTE)(w >> 8), m_file) == EOF);
	return (!m_bad);
}
