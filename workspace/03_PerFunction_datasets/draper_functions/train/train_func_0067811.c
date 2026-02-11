_AuFlush (AuServer *aud)
{
	AuInt32 size, todo;
	int write_stat;
	char *bufindex;

	if (aud->flags & AuServerFlagsIOError) return;

	size = todo = aud->bufptr - aud->buffer;
	bufindex = aud->bufptr = aud->buffer;


	while (size) {
	    errno = 0;
	    write_stat = WriteToServer(aud->fd, bufindex, (int) todo);
	    if (write_stat >= 0) {
		size -= write_stat;
		todo = size;
		bufindex += write_stat;
	    } else if (ETEST(errno)) {
		_AuWaitForWritable(aud);
#ifdef SUNSYSV
	    } else if (errno == 0) {
		_AuWaitForWritable(aud);
#endif
#ifdef EMSGSIZE
	    } else if (errno == EMSGSIZE) {
		if (todo > 1)
		  todo >>= 1;
		else
		  _AuWaitForWritable(aud);
#endif
	    } else if (errno != EINTR) {


		_AuIOError(aud);
	    }
	}
	aud->last_req = (char *)&_dummy_request;
}
