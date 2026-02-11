setAudioStream(int channel)
{
    IReadStream* astream = 0;
    if (channel > 127)
	channel = 127;
    else if (channel < 0)
	channel = 0;

    IReadFile* qf = m_pClipAudio;
    if (!qf)
	qf = m_pClip;

    while (qf && !astream && channel >= 0)
	astream = qf->GetStream(channel--, IReadStream::Audio);

    if (astream != m_pAudiostream)
    {
	double tpos = 0.0;
	if (m_pAudioRenderer)
	{
	    tpos = m_pAudioRenderer->GetTime();
	    delete m_pAudioRenderer;
	    m_pAudioRenderer = 0;
	}
	else if (m_pVideostream)
	    tpos = m_pVideostream->GetTime();

	if (m_pAudiostream)
	    m_pAudiostream->StopStreaming();

	m_pAudiostream = astream;
	createAudioRenderer();
	if (m_pAudioRenderer)
	{
	    m_pAudioRenderer->SeekTime(tpos);
	    m_pAudioRenderer->Start();
	}
    }
    return 0;
}
