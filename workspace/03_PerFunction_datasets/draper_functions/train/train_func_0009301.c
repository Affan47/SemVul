force_io(Stream_t *Stream,
		    char *buf, mt_off_t start, size_t len,
		    int (*io)(Stream_t *, char *, mt_off_t, size_t))
{
	int ret;
	int done=0;

	while(len){
		ret = io(Stream, buf, start, len);
		if ( ret <= 0 ){
			if (done)
				return done;
			else
				return ret;
		}
		start += ret;
		done += ret;
		len -= ret;
		buf += ret;
	}
	return done;
}
