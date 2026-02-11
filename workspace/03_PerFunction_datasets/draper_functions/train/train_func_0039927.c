write_rail_unicode_string(STREAM* s, RAIL_UNICODE_STRING* string)
{
	stream_write_uint16(s, string->length);
	if (string->length > 0)
	{
		stream_write(s, string->buffer, string->length);
	}
}
