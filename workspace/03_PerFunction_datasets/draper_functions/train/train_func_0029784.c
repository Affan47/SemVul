read_metadata_block_data_padding_cb_(FLAC__IOHandle handle, FLAC__IOCallback_Seek seek_cb, FLAC__StreamMetadata_Padding *block, unsigned block_length)
{
	(void)block;

	if(0 != seek_cb(handle, block_length, SEEK_CUR))
		return FLAC__METADATA_SIMPLE_ITERATOR_STATUS_SEEK_ERROR;

	return FLAC__METADATA_SIMPLE_ITERATOR_STATUS_OK;
}
