GetStreamInfo() const
{
    if (!m_pSeekInfo)
    {
	AVM_WRITE("ASF reader", "GetStreamInfo() no seek info\n");
    }
    if (m_StreamInfo.m_p->m_dLengthTime == 0.0)
    {
	size_t kfmax = 0;
	size_t kfmin = ~0U;
	uint_t kfchunks = 0;
	int64_t kfsize = 0;
	size_t fmax = 0;
	size_t fmin = ~0U;
	uint_t chunks = 0;
	int64_t size = 0;

	if (m_pSeekInfo)
	    for (size_t i = 0; i < m_pSeekInfo->size(); ++i)
	    {
		size_t l = (*m_pSeekInfo)[i].GetChunkLength();
		if ((*m_pSeekInfo)[i].IsKeyFrame() || m_bIsAudio)
		{
		    kfmax = (kfmax > l) ? kfmax : l;
		    kfmin = (kfmin < l) ? kfmin : l;
		    kfsize += l;
		    kfchunks++;
		}
		else
		{
		    fmax = (fmax > l) ? fmax : l;
		    fmin = (fmin < l) ? fmin : l;
		    size += l;
		    chunks++;
		}
	    }
	m_StreamInfo.m_p->setKfFrames(kfmax, kfmin, kfchunks, kfsize);
	m_StreamInfo.m_p->setFrames(fmax, fmin, chunks, size);

	double ft = 0;
	if (m_pSeekInfo && m_pSeekInfo->size())
	    ft = (*m_pSeekInfo)[0].object_start_time / 1000.;
	m_StreamInfo.m_p->m_dLengthTime = GetLengthTime() - ft;
	m_StreamInfo.m_p->m_iQuality = 0;

	if (m_bIsAudio)
	{
	    const WAVEFORMATEX& wfx = m_Header.hdr.aud.wfx;
	    m_StreamInfo.m_p->setAudio(wfx.nChannels, wfx.nSamplesPerSec,
				       wfx.wBitsPerSample, wfx.nAvgBytesPerSec);
	    m_StreamInfo.m_p->m_Type = StreamInfo::Audio;
	    m_StreamInfo.m_p->m_uiFormat = wfx.wFormatTag;
	    m_StreamInfo.m_p->m_iSampleSize = 1;
	}
	else
	{
	    const BITMAPINFOHEADER& bih = m_Header.hdr.vid.bih;
	    m_StreamInfo.m_p->setVideo(bih.biWidth, bih.biHeight, m_iMaxBitrate/8);
	    m_StreamInfo.m_p->m_Type = StreamInfo::Video;
	    m_StreamInfo.m_p->m_uiFormat = bih.biCompression;
	    m_StreamInfo.m_p->m_iSampleSize = 0;
	}
    }

    return new StreamInfo(m_StreamInfo);
}
