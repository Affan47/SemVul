GetFrameTime() const
{
    if (!m_pSeekInfo || !m_pSeekInfo->size())
	return 1./15.;

    return GetLengthTime()/(double)m_pSeekInfo->size();
}
