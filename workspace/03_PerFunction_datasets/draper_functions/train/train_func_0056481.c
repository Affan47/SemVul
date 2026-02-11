doallocate ()
{
	trace_with_mask("Streambuf::doallocate",STRMBUFTRACE);

	char* buf;
	buf = new char [1024];
	if (buf == NULL) {
		return EOF;
	}
	setb (buf, buf+1024, 1);

	return 1;
}
