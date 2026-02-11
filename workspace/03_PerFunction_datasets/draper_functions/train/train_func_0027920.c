underflow ()
{


	trace_with_mask("Socketbuf::underflow",STRMBUFTRACE);

	if (gptr () < egptr ())
	{
		return *(unsigned char*) gptr ();
	}

	if (base () == 0 &&
	    doallocate () == EOF)
	{
		return EOF;
	}

	int bufsz = unbuffered () ? 1 : MAXTCPFRAMESZ;


	int rval = sys_read (base (), bufsz);

	DL((STRMBUF,"Socketbuf::sys_read() returned %d bytes\n", rval));

	if (rval == EOF)
	{
		if (get_errno () != EWOULDBLOCK) {
			m_flags |= EOF_SEEN;
		}
		return EOF;
	}

	DL((STRMBUF,"Having read %d bytes from socket\n",rval));
	MemDump::dump_to_log (STRMBUF, "Data received:", base (), rval);


	setg (base (), base (), base () + rval);

	dump ();

	return (*(unsigned char*) gptr ());
}
