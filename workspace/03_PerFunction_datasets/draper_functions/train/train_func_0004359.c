CSerialPort_stream_lof(GB_STREAM *stream, int64_t *len)
{
	void *_object = stream->tag;
	int bytes;

	*len=0;
	if (!_object) return -1;

	if (ioctl(THIS->port,FIONREAD,&bytes)) return -1;
	*len = bytes;
	return 0;
}
