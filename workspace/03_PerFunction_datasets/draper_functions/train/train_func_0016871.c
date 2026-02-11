FLAC__bitwriter_get_write_crc8(FLAC__BitWriter *bw, FLAC__byte *crc)
{
	const FLAC__byte *buffer;
	size_t bytes;

	FLAC__ASSERT((bw->bits & 7) == 0);

	if(!FLAC__bitwriter_get_buffer(bw, &buffer, &bytes))
		return false;

	*crc = FLAC__crc8(buffer, bytes);
	FLAC__bitwriter_release_buffer(bw);
	return true;
}
