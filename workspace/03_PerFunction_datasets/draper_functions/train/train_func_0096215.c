cafebabe_constant_info_utf8_init(struct cafebabe_constant_info_utf8 *utf8,
	struct cafebabe_stream *s)
{
	if (cafebabe_stream_read_uint16(s, &utf8->length))
		goto out;

	utf8->bytes = cafebabe_stream_malloc(s, utf8->length);
	if (!utf8->bytes)
		goto out;

	for (uint16_t i = 0; i < utf8->length; ++i) {
		if (cafebabe_stream_read_uint8(s, &utf8->bytes[i]))
			goto out_bytes;
	}

	return 0;

out_bytes:
	free(utf8->bytes);
out:
	return 1;
}
