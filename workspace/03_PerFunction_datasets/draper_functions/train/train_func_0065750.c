runPull()
{
	SharedPtr<PacketTable> packetTable = m_track->m_packetTable;
	if (m_currentPacket >= static_cast<int>(packetTable->numPackets()))
	{
		m_outChunk->frameCount = 0;
		return;
	}
	assert(m_currentPacket < static_cast<int>(packetTable->numPackets()));

	ssize_t bytesPerPacket = packetTable->bytesPerPacket(m_currentPacket);
	assert(bytesPerPacket <= bufferSize());

	if (read(m_inChunk->buffer, bytesPerPacket) < bytesPerPacket)
	{
		reportReadError(0, m_track->f.framesPerPacket);
		return;
	}

	BitBuffer bitBuffer;
	BitBufferInit(&bitBuffer, static_cast<uint8_t *>(m_inChunk->buffer),
		bytesPerPacket);

	uint32_t numFrames;
	m_decoder->Decode(&bitBuffer, static_cast<uint8_t *>(m_outChunk->buffer),
		m_track->f.framesPerPacket, m_track->f.channelCount, &numFrames);
	m_outChunk->frameCount = numFrames;

	m_currentPacket++;
}
