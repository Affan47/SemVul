StreamInUtf8() const
	{
		unsigned char b = GetNextByte();
		if (m_input.good())
		{
			m_readahead.push_back(b);
		}
	}
