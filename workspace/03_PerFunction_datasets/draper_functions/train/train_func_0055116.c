tell_callback(FLAC__uint64 *absolute_byte_offset)
{
	FLAC__off_t pos;
	if(layer_==LAYER_STREAM)
		return ::FLAC__STREAM_ENCODER_TELL_STATUS_UNSUPPORTED;
	else if((pos = ftello(file_)) < 0)
		return FLAC__STREAM_ENCODER_TELL_STATUS_ERROR;
	else {
		*absolute_byte_offset = (FLAC__uint64)pos;
		return FLAC__STREAM_ENCODER_TELL_STATUS_OK;
	}
}
