bindStream(mrpt::utils::CStream * external_stream, mrpt::synch::CCriticalSection *csOptionalExternalStream)
{
	if (!m_data_stream_is_external) {
		delete m_data_stream;
		m_data_stream = NULL;
	}

	m_data_stream_is_external = true;
	m_data_stream = external_stream;
	m_data_stream_cs = csOptionalExternalStream;
}
