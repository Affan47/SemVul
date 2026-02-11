mpg123_getformat(mpg123_handle *mh, long *rate, int *channels, int *encoding)
{
	ALIGNCHECK(mh);
	if(mh == NULL) return MPG123_ERR;
	if(init_track(mh) == MPG123_ERR) return MPG123_ERR;

	if(rate != NULL) *rate = mh->af.rate;
	if(channels != NULL) *channels = mh->af.channels;
	if(encoding != NULL) *encoding = mh->af.encoding;
	mh->new_format = 0;
	return MPG123_OK;
}
