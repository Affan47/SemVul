CopyRangeTo2(BufferedTransformation &target, lword &begin, lword end, const std::string &channel, bool blocking) const
{
	if (!m_stream)
		return 0;

	if (begin == 0 && end == 1)
	{
		int result = m_stream->peek();
		if (result == char_traits<char>::eof())
			return 0;
		else
		{
			size_t blockedBytes = target.ChannelPut(channel, byte(result), blocking);
			begin += 1-blockedBytes;
			return blockedBytes;
		}
	}


	streampos current = m_stream->tellg();
	streampos endPosition = m_stream->seekg(0, ios::end).tellg();
	streampos newPosition = current + (streamoff)begin;

	if (newPosition >= endPosition)
	{
		m_stream->seekg(current);
		return 0;
	}
	m_stream->seekg(newPosition);
	try
	{
		assert(!m_waiting);
		lword copyMax = end-begin;
		size_t blockedBytes = const_cast<FileStore *>(this)->TransferTo2(target, copyMax, channel, blocking);
		begin += copyMax;
		if (blockedBytes)
		{
			const_cast<FileStore *>(this)->m_waiting = false;
			return blockedBytes;
		}
	}
	catch(...)
	{
		m_stream->clear();
		m_stream->seekg(current);
		throw;
	}
	m_stream->clear();
	m_stream->seekg(current);

	return 0;
}
