stream_lseek(mpg123_handle *fr, off_t pos, int whence)
{
	off_t ret;
	ret = fr->rdat.lseek(fr->rdat.filept, pos, whence);
	if (ret >= 0)	fr->rdat.filepos = ret;
	else
	{
		fr->err = MPG123_LSEEK_FAILED;
		ret = READER_ERROR;
	}
	return ret;
}
