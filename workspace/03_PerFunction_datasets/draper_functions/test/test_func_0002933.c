rdp_read_share_data_header(STREAM* s, uint16* length, uint8* type, uint32* share_id)
{

	stream_read_uint32(s, *share_id);
	stream_seek_uint8(s);
	stream_seek_uint8(s);
	stream_read_uint16(s, *length);
	stream_read_uint8(s, *type);
	stream_seek_uint8(s);
	stream_seek_uint16(s);
}
