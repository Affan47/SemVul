certificate_read_x509_certificate(CERT_BLOB* cert, CERT_INFO* info)
{
	STREAM* s;
	int length;
	uint8 padding;
	uint32 version;
	int modulus_length;
	int exponent_length;

	s = stream_new(0);
	s->p = s->data = cert->data;

	ber_read_sequence_tag(s, &length);

	ber_read_sequence_tag(s, &length);


	ber_read_contextual_tag(s, 0, &length, True);
	ber_read_integer(s, &version);
	version++;


	ber_read_integer(s, NULL);


	ber_read_sequence_tag(s, &length);
	stream_seek(s, length);


	ber_read_sequence_tag(s, &length);
	stream_seek(s, length);


	ber_read_sequence_tag(s, &length);
	stream_seek(s, length);


	ber_read_sequence_tag(s, &length);
	stream_seek(s, length);


	ber_read_sequence_tag(s, &length);


	ber_read_sequence_tag(s, &length);
	stream_seek(s, length);


	ber_read_bit_string(s, &length, &padding);


	ber_read_sequence_tag(s, &length);

	ber_read_integer_length(s, &modulus_length);


	do
	{
		stream_peek_uint8(s, padding);

		if (padding == 0)
		{
			stream_seek(s, 1);
			modulus_length--;
		}
	}
	while (padding == 0);

	freerdp_blob_alloc(&info->modulus, modulus_length);
	stream_read(s, info->modulus.data, modulus_length);

	ber_read_integer_length(s, &exponent_length);
	stream_read(s, &info->exponent[4 - exponent_length], exponent_length);
}
