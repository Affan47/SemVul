PeekWord32(word32 &value, ByteOrder order) const
{
	byte buf[4] = {0, 0, 0, 0};
	size_t len = Peek(buf, 4);

	if (order)
		value = (buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | buf [3];
	else
		value = (buf[3] << 24) | (buf[2] << 16) | (buf[1] << 8) | buf [0];

	return len;
}
