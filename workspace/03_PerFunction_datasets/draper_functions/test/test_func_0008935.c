grow (size_t length)
{
	if (length + 1 <= (m_buflen - (m_pEnd - m_psz))) return true;

	if (m_psz == 0)
	{
		if (length == 0) return true;
		m_psz = static_cast<char *>(g_try_malloc(length));
		if (m_psz == 0) return false;
		m_strlen = 0;
		m_buflen = length;
		m_pEnd = m_psz;
		*m_pEnd = 0;
		return true;
	}

	size_t new_length = length + (m_pEnd - m_psz) + 1;
	size_t end_offset = m_pEnd - m_psz;

	char * more = static_cast<char *>(g_try_realloc(static_cast<void *>(m_psz), new_length));
	if (more == 0) return false;
	m_psz = more;
	m_pEnd = m_psz + end_offset;
	m_buflen = new_length;
	return true;
}
