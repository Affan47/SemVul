plain_read(mpg123_handle *fr, void *buf, size_t count)
{
	ssize_t ret = fr->rdat.read(fr->rdat.filept, buf, count);
	if(VERBOSE3) debug2("read %li bytes of %li", (long)ret, (long)count);
	return ret;
}
