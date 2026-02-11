drdynvc_write_variable_uint(STREAM* stream, uint32 val)
{
	int cb;

	if (val <= 0xFF)
	{
		cb = 0;
		stream_write_uint8(stream, val);
	}
	else if (val <= 0xFFFF)
	{
		cb = 1;
		stream_write_uint16(stream, val);
	}
	else
	{
		cb = 3;
		stream_write_uint32(stream, val);
	}
	return cb;
}
