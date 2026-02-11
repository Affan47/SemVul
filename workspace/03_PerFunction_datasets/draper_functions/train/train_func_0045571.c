StartStreaming(const char* privname)
{
    if (m_pAudiodecoder)
	return 0;

    m_pAudiodecoder = CreateDecoderAudio((WAVEFORMATEX*)m_pFormat, privname);

    if (!m_pAudiodecoder)
    {
	AVM_WRITE("audio reader", "Failed to initialize audio decoder for format 0x%x\n",
		  ((WAVEFORMATEX*)m_pFormat)->wFormatTag);
	return -1;
    }

    m_uiMinSize = m_pAudiodecoder->GetMinSize();
    if (m_uiMinSize < MINSIZE)
	m_uiMinSize = MINSIZE;

    m_uiSrcSize = m_pAudiodecoder->GetSrcSize(SRCSIZE);
    if (m_uiSrcSize < SRCSIZE)
	m_uiSrcSize = SRCSIZE;

    if (rem_limit < (MINSIZE + m_uiSrcSize)) {
	rem_limit = MINSIZE + m_uiSrcSize;
	rem_buffer.reserve(rem_limit + PADDING);
	memset(rem_buffer.begin(), 0, rem_limit + PADDING);
    }
    AVM_WRITE("audio reader", 1, "Initialize audio decoder - minsize: %" PRIsz " srsize: %" PRIsz "\n", m_uiMinSize, m_uiSrcSize);
    return 0;
}
