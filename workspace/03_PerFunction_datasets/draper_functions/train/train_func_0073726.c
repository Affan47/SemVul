Put2(const byte *begin, size_t length, int messageEnd, bool blocking)
{
	FILTER_BEGIN;
	while (m_inputPosition < length)
	{
		if (m_bytePos == 0)
			memset(m_outBuf, 0, m_outputBlockSize);

		{
		unsigned int b = begin[m_inputPosition++], bitsLeftInSource = 8;
		while (true)
		{
			assert(m_bitPos < m_bitsPerChar);
			unsigned int bitsLeftInTarget = m_bitsPerChar-m_bitPos;
			m_outBuf[m_bytePos] |= b >> (8-bitsLeftInTarget);
			if (bitsLeftInSource >= bitsLeftInTarget)
			{
				m_bitPos = 0;
				++m_bytePos;
				bitsLeftInSource -= bitsLeftInTarget;
				if (bitsLeftInSource == 0)
					break;
				b <<= bitsLeftInTarget;
				b &= 0xff;
			}
			else
			{
				m_bitPos += bitsLeftInSource;
				break;
			}
		}
		}

		assert(m_bytePos <= m_outputBlockSize);
		if (m_bytePos == m_outputBlockSize)
		{
			int i;
			for (i=0; i<m_bytePos; i++)
			{
				assert(m_outBuf[i] < (1 << m_bitsPerChar));
				m_outBuf[i] = m_alphabet[m_outBuf[i]];
			}
			FILTER_OUTPUT(1, m_outBuf, m_outputBlockSize, 0);

			m_bytePos = m_bitPos = 0;
		}
	}
	if (messageEnd)
	{
		if (m_bitPos > 0)
			++m_bytePos;

		int i;
		for (i=0; i<m_bytePos; i++)
			m_outBuf[i] = m_alphabet[m_outBuf[i]];

		if (m_padding != -1 && m_bytePos > 0)
		{
			memset(m_outBuf+m_bytePos, m_padding, m_outputBlockSize-m_bytePos);
			m_bytePos = m_outputBlockSize;
		}
		FILTER_OUTPUT(2, m_outBuf, m_bytePos, messageEnd);
		m_bytePos = m_bitPos = 0;
	}
	FILTER_END_NO_MESSAGE_END;
}
