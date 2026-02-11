Zap()
{
	if( !m_external )
		memset(m_memBlock, 0, m_blockSize);
	m_dataSize = 0;
}
