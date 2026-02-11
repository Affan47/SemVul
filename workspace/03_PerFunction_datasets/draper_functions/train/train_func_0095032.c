PeekWord16(word16 &value, ByteOrder order) const
{
	byte buf[2] = {0, 0};
	size_t len = Peek(buf, 2);

	if (order)
		value = (buf[0] << 8) | buf[1];
	else
		value = (buf[1] << 8) | buf[0];

	return len;
}
