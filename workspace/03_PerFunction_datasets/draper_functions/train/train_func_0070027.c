mpg123_framebyframe_decode(mpg123_handle *mh, off_t *num, unsigned char **audio, size_t *bytes)
{
	ALIGNCHECK(mh);
	if(bytes == NULL) return MPG123_ERR_NULL;
	if(audio == NULL) return MPG123_ERR_NULL;
	if(mh == NULL) return MPG123_BAD_HANDLE;
	if(mh->buffer.size < mh->outblock) return MPG123_NO_SPACE;

	*bytes = 0;
	mh->buffer.fill = 0;
	if(!mh->to_decode) return MPG123_OK;

	if(num != NULL) *num = mh->num;
	debug("decoding");
	decode_the_frame(mh);
	mh->to_decode = mh->to_ignore = FALSE;
	mh->buffer.p = mh->buffer.data;
#ifdef GAPLESS

	frame_buffercheck(mh);
#endif
	*audio = mh->buffer.p;
	*bytes = mh->buffer.fill;
	return MPG123_OK;
}
