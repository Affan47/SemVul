TransferTo2(BufferedTransformation &target, lword &transferBytes, const std::string &channel, bool blocking)
{
	if (!m_stream)
	{
		transferBytes = 0;
		return 0;
	}

	lword size=transferBytes;
	transferBytes = 0;

	if (m_waiting)
		goto output;

	while (size && m_stream->good())
	{
		{
		size_t spaceSize = 1024;
		m_space = HelpCreatePutSpace(target, channel, 1, UnsignedMin(size_t(0)-1, size), spaceSize);

		m_stream->read((char *)m_space, (unsigned int)STDMIN(size, (lword)spaceSize));
		}
		m_len = (size_t)m_stream->gcount();
		size_t blockedBytes;
output:
		blockedBytes = target.ChannelPutModifiable2(channel, m_space, m_len, 0, blocking);
		m_waiting = blockedBytes > 0;
		if (m_waiting)
			return blockedBytes;
		size -= m_len;
		transferBytes += m_len;
	}

	if (!m_stream->good() && !m_stream->eof())
		throw ReadErr();

	return 0;
}
