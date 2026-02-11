writeVHDR()
{
	uint32_t chunkSize;
	uint32_t oneShotSamples, repeatSamples, samplesPerRepeat;
	uint16_t sampleRate;
	uint8_t octaves, compression;
	uint32_t volume;


	if (m_VHDR_offset == 0)
		m_VHDR_offset = m_fh->tell();
	else
		m_fh->seek(m_VHDR_offset, File::SeekFromBeginning);

	Track *track = getTrack();

	m_fh->write("VHDR", 4);

	chunkSize = 20;
	writeU32(&chunkSize);


	oneShotSamples = track->totalfframes;
	writeU32(&oneShotSamples);
	repeatSamples = 0;
	writeU32(&repeatSamples);
	samplesPerRepeat = 0;
	writeU32(&samplesPerRepeat);

	sampleRate = track->f.sampleRate;
	writeU16(&sampleRate);

	octaves = 0;
	compression = 0;
	writeU8(&octaves);
	writeU8(&compression);


	volume = 65536;
	writeU32(&volume);

	return AF_SUCCEED;
}
