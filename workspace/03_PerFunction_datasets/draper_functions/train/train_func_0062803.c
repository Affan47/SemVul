update_read_coord(STREAM* s, sint16* coord, boolean delta)
{
	sint8 byte;

	if (delta)
	{
		stream_read_uint8(s, byte);
		*coord += byte;
	}
	else
	{
		stream_read_uint16(s, *coord);
	}
}
