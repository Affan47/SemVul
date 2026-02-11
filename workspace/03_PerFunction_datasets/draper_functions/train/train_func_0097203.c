Put(const byte *inString, size_t length)
{
	assert(m_size + length <= m_buffer.size());
	byte *end = (m_size < size_t(m_buffer.end()-m_begin)) ? m_begin + m_size : m_begin + m_size - m_buffer.size();
	size_t len = STDMIN(length, size_t(m_buffer.end()-end));
	memcpy(end, inString, len);
	if (len < length)
		memcpy(m_buffer, inString+len, length-len);
	m_size += length;
}
