LazyPut(const byte *inString, size_t size)
{
	if (m_lazyLength > 0)
		FinalizeLazyPut();

	if (inString == m_tail->buf+m_tail->m_tail)
		Put(inString, size);
	else
	{
		m_lazyString = const_cast<byte *>(inString);
		m_lazyLength = size;
		m_lazyStringModifiable = false;
	}
}
