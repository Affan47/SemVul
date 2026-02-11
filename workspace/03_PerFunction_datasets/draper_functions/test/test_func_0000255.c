write_metadata_block_data_padding_cb_(FLAC__IOHandle handle, FLAC__IOCallback_Write write_cb, const FLAC__StreamMetadata_Padding *block, unsigned block_length)
{
	unsigned i, n = block_length;
	FLAC__byte buffer[1024];

	(void)block;

	memset(buffer, 0, 1024);

	for(i = 0; i < n/1024; i++)
		if(write_cb(buffer, 1, 1024, handle) != 1024)
			return false;

	n %= 1024;

	if(write_cb(buffer, 1, n, handle) != n)
		return false;

	return true;
}
