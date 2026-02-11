flac_decoder_length_callback(const FLAC__StreamDecoder *decoder, FLAC__uint64 *stream_length, void *client_data)
{
	const EncoderSession *e = (EncoderSession*)client_data;
    const FLACDecoderData *data = &e->fmt.flac.client_data;
	(void)decoder;

	if(data->filesize < 0)
		return FLAC__STREAM_DECODER_LENGTH_STATUS_ERROR;
	else {
		*stream_length = (FLAC__uint64)data->filesize;
		return FLAC__STREAM_DECODER_LENGTH_STATUS_OK;
	}
}
