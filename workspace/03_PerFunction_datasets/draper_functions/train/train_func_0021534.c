seek_to_first_metadata_block_cb_(FLAC__IOHandle handle, FLAC__IOCallback_Read read_cb, FLAC__IOCallback_Seek seek_cb)
{
	FLAC__byte buffer[4];
	size_t n;
	unsigned i;

	FLAC__ASSERT(FLAC__STREAM_SYNC_LENGTH == sizeof(buffer));


	errno = 0;
	n = read_cb(buffer, 1, 4, handle);
	if(errno)
		return 1;
	else if(n != 4)
		return 3;
	else if(0 == memcmp(buffer, "ID3", 3)) {
		unsigned tag_length = 0;


		if(seek_cb(handle, 2, SEEK_CUR) < 0)
			return 2;


		for(i = 0; i < 4; i++) {
			if(read_cb(buffer, 1, 1, handle) < 1 || buffer[0] & 0x80)
				return 1;
			tag_length <<= 7;
			tag_length |= (buffer[0] & 0x7f);
		}


		if(seek_cb(handle, tag_length, SEEK_CUR) < 0)
			return 2;


		errno = 0;
		n = read_cb(buffer, 1, 4, handle);
		if(errno)
			return 1;
		else if(n != 4)
			return 3;
	}


	if(0 == memcmp(FLAC__STREAM_SYNC_STRING, buffer, FLAC__STREAM_SYNC_LENGTH))
		return 0;
	else
		return 3;
}
