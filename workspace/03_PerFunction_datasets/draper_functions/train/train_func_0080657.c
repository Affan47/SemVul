operator bool() const
	{
		return m_input.good() || (!m_readahead.empty() && m_readahead[0] != Stream::eof());
	}
