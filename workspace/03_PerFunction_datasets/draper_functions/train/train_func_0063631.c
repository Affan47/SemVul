GetLengthTime() const
{
    if (m_pSeekInfo && m_pSeekInfo->size() > 0)
    {
	return ((*m_pSeekInfo)[m_pSeekInfo->size() - 1].object_start_time) / 1000.;
    }

    if (m_pHandler->m_Header.play_time <= m_pHandler->m_Header.preroll)
	return (double) 0x7fffffff;

    return (double)(m_pHandler->m_Header.play_time - m_pHandler->m_Header.preroll) / 10000000.;
}
