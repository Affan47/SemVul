recordData(const unsigned char *data, unsigned int length) {
	m_recorded.reserve(m_recorded.size() + length);
	for (unsigned int i = 0; i < length; ++i) {
		m_recorded.push_back((char)data[i]);
	}
}
