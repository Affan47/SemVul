read_callback(FLAC__byte buffer[], size_t *bytes)
{
	if(*bytes > 0) {
		*bytes = fread(buffer, sizeof(FLAC__byte), *bytes, file_);
		if(ferror(file_))
			return ::FLAC__STREAM_ENCODER_READ_STATUS_ABORT;
		else if(*bytes == 0)
			return ::FLAC__STREAM_ENCODER_READ_STATUS_END_OF_STREAM;
		else
			return ::FLAC__STREAM_ENCODER_READ_STATUS_CONTINUE;
	}
	else
		return ::FLAC__STREAM_ENCODER_READ_STATUS_ABORT;
}
