setVideoBuffering()
{
    lockThreads("SetVideoBuffered");

    if (m_pVideostream)
    {
	IImageAllocator* ia = (m_bVideoDirect && m_VideoRenderers.size()) ? m_VideoRenderers[0] : 0;
	uint_t bufs = (m_bVideoBuffered) ? 6 : 1;


	m_pVideostream->SetBuffering(bufs, ia);
    }
    unlockThreads();
}
