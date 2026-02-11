copyNextWord(char *pBuffer, size_t length)
{
	size_t index = 0;
	m_DataIt = getNextWord<DataArrayIt>(m_DataIt, m_DataItEnd);
	while ( m_DataIt != m_DataItEnd && !isSeparator(*m_DataIt) )
	{
		pBuffer[index] = *m_DataIt;
		index++;
		if (index == length-1)
			break;
		++m_DataIt;
	}

	ai_assert(index < length);
	pBuffer[index] = '\0';
}
