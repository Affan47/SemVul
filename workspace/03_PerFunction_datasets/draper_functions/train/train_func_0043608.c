LongestMatch(unsigned int &bestMatch) const
{
	assert(m_previousLength < MAX_MATCH);

	bestMatch = 0;
	unsigned int bestLength = STDMAX(m_previousLength, (unsigned int)MIN_MATCH-1);
	if (m_lookahead <= bestLength)
		return 0;

	const byte *scan = m_byteBuffer + m_stringStart, *scanEnd = scan + STDMIN((unsigned int)MAX_MATCH, m_lookahead);
	unsigned int limit = m_stringStart > (DSIZE-MAX_MATCH) ? m_stringStart - (DSIZE-MAX_MATCH) : 0;
	unsigned int current = m_head[ComputeHash(scan)];

	unsigned int chainLength = MAX_CHAIN_LENGTH;
	if (m_previousLength >= GOOD_MATCH)
		chainLength >>= 2;

	while (current > limit && --chainLength > 0)
	{
		const byte *match = m_byteBuffer + current;
		assert(scan + bestLength < m_byteBuffer + m_stringStart + m_lookahead);
		if (scan[bestLength-1] == match[bestLength-1] && scan[bestLength] == match[bestLength] && scan[0] == match[0] && scan[1] == match[1])
		{
			assert(scan[2] == match[2]);
			unsigned int len = (unsigned int)(
#if defined(_STDEXT_BEGIN) && !(defined(_MSC_VER) && (_MSC_VER < 1400 || _MSC_VER >= 1600)) && !defined(_STLPORT_VERSION)
				stdext::unchecked_mismatch
#else
				std::mismatch
#endif
#if _MSC_VER >= 1600
				(stdext::make_unchecked_array_iterator(scan)+3, stdext::make_unchecked_array_iterator(scanEnd), stdext::make_unchecked_array_iterator(match)+3).first - stdext::make_unchecked_array_iterator(scan));
#else
				(scan+3, scanEnd, match+3).first - scan);
#endif
			assert(len != bestLength);
			if (len > bestLength)
			{
				bestLength = len;
				bestMatch = current;
				if (len == (scanEnd - scan))
					break;
			}
		}
		current = m_prev[current & DMASK];
	}
	return (bestMatch > 0) ? bestLength : 0;
}
