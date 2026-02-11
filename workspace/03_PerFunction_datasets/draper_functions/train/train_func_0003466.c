ber_read_bit_string(STREAM* s, int* length, uint8* padding)
{
	ber_read_universal_tag(s, BER_TAG_BIT_STRING, False);
	ber_read_length(s, length);
	stream_read_uint8(s, *padding);

	return True;
}
