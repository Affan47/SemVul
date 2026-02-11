runPush()
{
	AFframecount framesToWrite = m_inChunk->frameCount;
	AFframecount samplesToWrite = m_inChunk->frameCount * m_inChunk->f.channelCount;
	int framesize = m_inChunk->f.channelCount;

	assert(m_track->f.compressionType == AF_COMPRESSION_G711_ULAW ||
		m_track->f.compressionType == AF_COMPRESSION_G711_ALAW);


	if (m_track->f.compressionType == AF_COMPRESSION_G711_ULAW)
		linear2ulaw_buf(static_cast<const int16_t *>(m_inChunk->buffer),
			static_cast<uint8_t *>(m_outChunk->buffer), samplesToWrite);
	else
		linear2alaw_buf(static_cast<const int16_t *>(m_inChunk->buffer),
			static_cast<uint8_t *>(m_outChunk->buffer), samplesToWrite);


	ssize_t bytesWritten = write(m_outChunk->buffer, framesize * framesToWrite);
	AFframecount framesWritten = bytesWritten >= 0 ? bytesWritten / framesize : 0;

	if (framesWritten != framesToWrite)
		reportWriteError(framesWritten, framesToWrite);

	m_track->nextfframe += framesWritten;
	m_track->totalfframes = m_track->nextfframe;

	assert(!canSeek() || (tell() == m_track->fpos_next_frame));
}
