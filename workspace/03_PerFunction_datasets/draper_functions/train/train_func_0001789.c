dwrite(const void* b, size_t size)
{
    const char* buffer = (const char*) b;
    if (m_lfd < 0)
    {
	if (m_lfd == -12345)
	{
	    if (getenv("WRITE_ASF"))
	    {

		char tmpfilename[256];
		char* tmpdir = getenv("TMPDIR");
		strncpy(tmpfilename, (tmpdir) ? tmpdir : "/tmp", 240);
		tmpfilename[240] = 0;
		strcat(tmpfilename, "/asfXXXXXX");
		m_lfd = mkstemp(tmpfilename);
		AVM_WRITE("ASF network reader", "Writing ASF file: %s  (%d)\n", tmpfilename, m_lfd);
	    }
	    else
	    {
		AVM_WRITE("ASF network reader", "\n\n"
			  "\tIf you wish to store the stream into a local file\n"
			  "\tyou may try to use this before starting aviplay:\n"
			  "\t\texport WRITE_ASF=1\n"
			  "\tthis will create /tmp/asfXXXXX with received data\n\n");

		m_lfd = -1;
	    }
	}
        if (m_lfd < 0)
	    return -1;
    }
    while (size > 0)
    {
	ssize_t i = ::write(m_lfd, buffer, size);
	if (i < 0)
            return i;
	buffer += i;
	size -= i;
    }
    fsync(m_lfd);
    return 0;
}
