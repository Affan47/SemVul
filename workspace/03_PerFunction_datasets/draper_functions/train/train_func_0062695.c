writeToStringHex(char* buffer) const
{
	char* buf = buffer;
	char fake[128];
	uint32_t written = 0;
	if (buffer == NULL)
		buf = fake;
	written = sprintf(buf,"%lu:",static_cast<long unsigned>(m_count));
	if (buf != fake)
		buf += written;
	for (uint32_t i = 0;i < m_count;++i)
	{
		written += sprintf(buf," 0x%lX",static_cast<long unsigned>(m_data[i]));
		if (buf != fake)
			buf = buffer + written;
	}
	return (int32_t) written;
}
