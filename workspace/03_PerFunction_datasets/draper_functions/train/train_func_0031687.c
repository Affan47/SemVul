Flush()
{
    ReadStream::Flush();
    if (m_pVideodecoder)
	m_pVideodecoder->Flush();

    if (m_pQueue)
	m_pQueue->Flush();
    m_pFrame = 0;
    Update();

    m_bHadKeyFrame = false;

}
