unpack_uint32_(FLAC__byte *b, unsigned bytes)
{
	FLAC__uint32 ret = 0;
	unsigned i;

	for(i = 0; i < bytes; i++)
		ret = (ret << 8) | (FLAC__uint32)(*b++);

	return ret;
}
