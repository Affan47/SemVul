ReadPacket()
{
    for (size_t i = 0; i < m_Packets.capacity() - 2; ++i)
    {
	if (m_Packets.size() > 0)
	    break;

	if (m_pHandler->readPacket() < 0)
	{
	    if (m_dLength < m_dTimestamp)
		m_dLength = m_dTimestamp;
	    return 0;
	}
    }

    if (!m_Packets.size())
	return 0;

    Locker locker(m_pHandler->m_Mutex);
    StreamPacket* p = m_Packets.front();
    m_Packets.pop();
    m_dTimestamp = (double)p->GetTimestamp() / (double)AV_TIME_BASE;

    if (m_dLength < m_dTimestamp)
	m_dLength = m_dTimestamp;


    return p;
}
