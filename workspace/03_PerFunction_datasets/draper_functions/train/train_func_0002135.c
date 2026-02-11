read_metadata_block_data_cuesheet_cb_(FLAC__IOHandle handle, FLAC__IOCallback_Read read_cb, FLAC__StreamMetadata_CueSheet *block)
{
	unsigned i, len;
	FLAC__Metadata_SimpleIteratorStatus status;
	FLAC__byte buffer[1024];

	FLAC__ASSERT((FLAC__STREAM_METADATA_CUESHEET_IS_CD_LEN + FLAC__STREAM_METADATA_CUESHEET_RESERVED_LEN)/8 <= sizeof(buffer));
	FLAC__ASSERT(sizeof(FLAC__uint64) <= sizeof(buffer));

	FLAC__ASSERT(FLAC__STREAM_METADATA_CUESHEET_MEDIA_CATALOG_NUMBER_LEN % 8 == 0);
	len = FLAC__STREAM_METADATA_CUESHEET_MEDIA_CATALOG_NUMBER_LEN / 8;
	if(read_cb(block->media_catalog_number, 1, len, handle) != len)
		return FLAC__METADATA_SIMPLE_ITERATOR_STATUS_READ_ERROR;

	FLAC__ASSERT(FLAC__STREAM_METADATA_CUESHEET_LEAD_IN_LEN % 8 == 0);
	len = FLAC__STREAM_METADATA_CUESHEET_LEAD_IN_LEN / 8;
	if(read_cb(buffer, 1, len, handle) != len)
		return FLAC__METADATA_SIMPLE_ITERATOR_STATUS_READ_ERROR;
	block->lead_in = unpack_uint64_(buffer, len);

	FLAC__ASSERT((FLAC__STREAM_METADATA_CUESHEET_IS_CD_LEN + FLAC__STREAM_METADATA_CUESHEET_RESERVED_LEN) % 8 == 0);
	len = (FLAC__STREAM_METADATA_CUESHEET_IS_CD_LEN + FLAC__STREAM_METADATA_CUESHEET_RESERVED_LEN) / 8;
	if(read_cb(buffer, 1, len, handle) != len)
		return FLAC__METADATA_SIMPLE_ITERATOR_STATUS_READ_ERROR;
	block->is_cd = buffer[0]&0x80? true : false;

	FLAC__ASSERT(FLAC__STREAM_METADATA_CUESHEET_NUM_TRACKS_LEN % 8 == 0);
	len = FLAC__STREAM_METADATA_CUESHEET_NUM_TRACKS_LEN / 8;
	if(read_cb(buffer, 1, len, handle) != len)
		return FLAC__METADATA_SIMPLE_ITERATOR_STATUS_READ_ERROR;
	block->num_tracks = unpack_uint32_(buffer, len);

	if(block->num_tracks == 0) {
		block->tracks = 0;
	}
	else if(0 == (block->tracks = calloc(block->num_tracks, sizeof(FLAC__StreamMetadata_CueSheet_Track))))
		return FLAC__METADATA_SIMPLE_ITERATOR_STATUS_MEMORY_ALLOCATION_ERROR;

	for(i = 0; i < block->num_tracks; i++) {
		if(FLAC__METADATA_SIMPLE_ITERATOR_STATUS_OK != (status = read_metadata_block_data_cuesheet_track_cb_(handle, read_cb, block->tracks + i)))
			return status;
	}

	return FLAC__METADATA_SIMPLE_ITERATOR_STATUS_OK;
}
