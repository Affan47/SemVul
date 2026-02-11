PrevKeyFrame()
{
    if (!IsPlaying())
	return -1;

    int r = 0;
    if (lockThreads("PrevKeyFrame") == 0)
    {
	if (m_pVideostream && m_pVideostream->GetPos())
	{
	    framepos_t cpos = m_pVideostream->GetPos();
	    framepos_t npos = m_pVideostream->SeekToPrevKeyFrame();
	    if (avm_get_time_diff(avm_get_time_us(), m_llPgPrevTime) < 0.3)
	    {
		framepos_t p = npos;
		while (npos > 0 && npos >= m_uiPgPrevPos)
		{
		    npos = m_pVideostream->SeekToPrevKeyFrame();
		    if (p == npos)
			break;
		}
	    }

	    if ((cpos - npos < 5) && !IsPaused())
	    {
		m_pVideostream->Seek(npos);
		npos = m_pVideostream->SeekToPrevKeyFrame();
	    }
	    m_llPgPrevTime = avm_get_time_us();
	    m_uiPgPrevPos = npos;

	    if (npos != m_pVideostream->ERR)
	    {

		double pos = m_pVideostream->GetTime();
		if (m_pAudioRenderer)
		    m_pAudioRenderer->SeekTime(pos > 0. ? pos : 0.);
	    }
	    drawFrame();
	}
	else if (m_pAudioRenderer)
	    m_pAudioRenderer->SeekTime(m_pAudioRenderer->GetTime() - 1.);

	unlockThreads();
    }

    return r;
}
