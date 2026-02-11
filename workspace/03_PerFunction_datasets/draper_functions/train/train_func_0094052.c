VideoStreamCount()
    {
	if (m_pHandler && !m_vstreams.size())
	{
	    if (!m_astreams.size() && !IsValid())
		return 0;
	    m_vstreams.resize(m_pHandler->GetStreamCount(IStream::Video));
	    for (uint_t i = 0; i < m_vstreams.size(); i++)
                m_vstreams[i] = 0;
	}
	return m_vstreams.size();
    }
