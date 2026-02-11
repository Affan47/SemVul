Stop()
{
    if (!m_vstatus)
	return -1;
    m_pVideoEnc->Stop();
    delete[] m_pBuffer;
    m_pBuffer = 0;
    m_vstatus = 0;
    return 0;
}
