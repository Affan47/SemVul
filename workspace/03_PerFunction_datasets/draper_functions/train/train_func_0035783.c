stream_decoder_tell_callback_(const FLAC__StreamDecoder *decoder, FLAC__uint64 *absolute_byte_offset, void *client_data)
{
	StreamDecoderClientData *dcd = (StreamDecoderClientData*)client_data;
	FLAC__off_t offset;

	(void)decoder;

	if(0 == dcd) {
		printf("ERROR: client_data in tell callback is NULL\n");
		return FLAC__STREAM_DECODER_TELL_STATUS_ERROR;
	}

	if(dcd->error_occurred)
		return FLAC__STREAM_DECODER_TELL_STATUS_ERROR;

	offset = ftello(dcd->file);
	*absolute_byte_offset = (FLAC__uint64)offset;

	if(offset < 0) {
		dcd->error_occurred = true;
		return FLAC__STREAM_DECODER_TELL_STATUS_ERROR;
	}

	return FLAC__STREAM_DECODER_TELL_STATUS_OK;
}
