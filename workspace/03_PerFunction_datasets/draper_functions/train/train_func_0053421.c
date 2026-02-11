RewindIgnore()
{
	extra_headersptr=0;
	if (mio.fd() >= 0)
	{
		if (mio.Rewind() < 0)	seekerr();
		return;
	}
	bufptr=buffer;
}
