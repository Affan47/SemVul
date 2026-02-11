flushBufferByte() {
	const char* valueAsBytes = (const char*)&m_combined;
	for (unsigned int i = 0; i < sizeof(unsigned int); ++i) {
		m_Pipe->sendByte(valueAsBytes[i]);
	}
	m_bitsLeft = 32;
	m_combined = 0;
	return GLE_IMAGE_ERROR_NONE;
}
