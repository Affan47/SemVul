writeToStream(mrpt::utils::CStream &out, int *version) const
{
	if (version)
		*version = 1;
	else
	{
		uint32_t i,n = m_data.size();
        out << m_pgn;
        out << m_src_address;
        out << m_priority;
        out << m_pdu_format;
        out << m_pdu_spec;
        out << m_data_length;
		out << n;

		for(i=0;i<n;i++)
			out << m_data[i];

		n = m_raw_frame.size();
		out << n;
		for(i=0;i<n;i++)
			out << uint8_t(m_raw_frame[i]);

		out << sensorLabel
		    << timestamp;
	}
}
