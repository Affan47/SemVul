ExtraHeaders(const Buffer &buf)
{
	if ( extra_headers )
	{
		delete[] extra_headers;
		extra_headers=0;
	}
	extra_headersptr=0;
	if (!buf.Length())	return;

	extra_headers=new char[buf.Length()+1];
	if (!extra_headers)	outofmem();
	memcpy(extra_headers, (const char *)buf, buf.Length());
	extra_headers[buf.Length()]=0;
	extra_headersptr=extra_headers;
	if (!*extra_headersptr)	extra_headersptr=0;
}
