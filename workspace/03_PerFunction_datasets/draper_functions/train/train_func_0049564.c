cgi_getfiles( int (*start_file)(const char *, const char *, void *),
		int (*file)(const char *, size_t, void *),
		void (*end_file)(void *), size_t filenum, void *voidarg)
{
	struct cgigetfileinfo gfi;

	gfi.start_file=start_file;
	gfi.file=file;
	gfi.end_file=end_file;
	gfi.filenum=filenum;
	gfi.voidarg=voidarg;

	if (rfc2045p) rfc2045_decode(rfc2045p, &cgifiledecode, &gfi);
	if (gfi.filenum)	return (-1);
	return (0);
}
