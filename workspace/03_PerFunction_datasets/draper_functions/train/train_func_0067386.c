GetStream(uint_t stream_id,
					   IStream::StreamType type)
{
    int t;
    uint_t cnt = 0;
    switch (type)
    {
    case IStream::Audio: t = AVMEDIA_TYPE_AUDIO; break;
    case IStream::Video: t = AVMEDIA_TYPE_VIDEO; break;
    default: return 0;
    }

    for (unsigned i = 0; i < m_pContext->nb_streams; ++i)
    {
	if (m_pContext->streams[i]->codec->codec_type == t)
	{
	    if (cnt == stream_id)
		return m_Streams[i];
	    cnt++;
	}
    }

    return 0;
}
