license_read_binary_blob(STREAM* s, LICENSE_BLOB* blob)
{
	uint16 wBlobType;

	stream_read_uint16(s, wBlobType);

	if (blob->type != wBlobType && blob->type != BB_ANY_BLOB)
	{
		printf("license binary blob type does not match expected type.\n");
		return;
	}

	blob->type = wBlobType;

	stream_read_uint16(s, blob->length);

	blob->data = (uint8*) xmalloc(blob->length);

	stream_read(s, blob->data, blob->length);
}
