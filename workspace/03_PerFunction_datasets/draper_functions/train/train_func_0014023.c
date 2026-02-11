StreamInUtf16() const
	{
		unsigned long ch = 0;
		unsigned char bytes[2];
		int nBigEnd = (m_charSet == utf16be) ? 0 : 1;

		bytes[0] = GetNextByte();
		bytes[1] = GetNextByte();
		if (!m_input.good())
		{
			return;
		}
		ch = (static_cast<unsigned long>(bytes[nBigEnd]) << 8) |
			static_cast<unsigned long>(bytes[1 ^ nBigEnd]);

		if (ch >= 0xDC00 && ch < 0xE000)
		{

			QueueUnicodeCodepoint(m_readahead, CP_REPLACEMENT_CHARACTER);
			return;
		}
		else if (ch >= 0xD800 && ch < 0xDC00)
		{


			for (;;)
			{
				bytes[0] = GetNextByte();
				bytes[1] = GetNextByte();
				if (!m_input.good())
				{
					QueueUnicodeCodepoint(m_readahead, CP_REPLACEMENT_CHARACTER);
					return;
				}
				unsigned long chLow = (static_cast<unsigned long>(bytes[nBigEnd]) << 8) |
					static_cast<unsigned long>(bytes[1 ^ nBigEnd]);
				if (chLow < 0xDC00 || ch >= 0xE000)
				{

					QueueUnicodeCodepoint(m_readahead, CP_REPLACEMENT_CHARACTER);


					if (chLow < 0xD800 || ch >= 0xE000)
					{

						QueueUnicodeCodepoint(m_readahead, ch);
						return;
					}
					else
					{

						ch = chLow;
						continue;
					}
				}


				ch &= 0x3FF;
				ch <<= 10;


				ch |= (chLow & 0x3FF);


				ch += 0x10000;
			}
		}

		QueueUnicodeCodepoint(m_readahead, ch);
	}
