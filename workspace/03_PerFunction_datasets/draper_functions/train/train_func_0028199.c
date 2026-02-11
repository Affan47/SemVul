EndBlock(bool eof)
{
	if (m_blockLength == 0 && !eof)
		return;

	if (m_deflateLevel == 0)
	{
		EncodeBlock(eof, STORED);

		if (m_compressibleDeflateLevel > 0 && ++m_detectCount == m_detectSkip)
		{
			m_deflateLevel = m_compressibleDeflateLevel;
			m_detectCount = 1;
		}
	}
	else
	{
		unsigned long storedLen = 8*((unsigned long)m_blockLength+4) + RoundUpToMultipleOf(m_bitsBuffered+3, 8U)-m_bitsBuffered;

		StartCounting();
		EncodeBlock(eof, STATIC);
		unsigned long staticLen = FinishCounting();

		unsigned long dynamicLen;
		if (m_blockLength < 128 && m_deflateLevel < 8)
			dynamicLen = ULONG_MAX;
		else
		{
			StartCounting();
			EncodeBlock(eof, DYNAMIC);
			dynamicLen = FinishCounting();
		}

		if (storedLen <= staticLen && storedLen <= dynamicLen)
		{
			EncodeBlock(eof, STORED);

			if (m_compressibleDeflateLevel > 0)
			{
				if (m_detectSkip)
					m_deflateLevel = 0;
				m_detectSkip = m_detectSkip ? STDMIN(2*m_detectSkip, 128U) : 1;
			}
		}
		else
		{
			if (staticLen <= dynamicLen)
				EncodeBlock(eof, STATIC);
			else
				EncodeBlock(eof, DYNAMIC);

			if (m_compressibleDeflateLevel > 0)
				m_detectSkip = 0;
		}
	}

	m_matchBufferEnd = 0;
	m_blockStart += m_blockLength;
	m_blockLength = 0;
	fill(m_literalCounts.begin(), m_literalCounts.end(), 0);
	fill(m_distanceCounts.begin(), m_distanceCounts.end(), 0);
}
