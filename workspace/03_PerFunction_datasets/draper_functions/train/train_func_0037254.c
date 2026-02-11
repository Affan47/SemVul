transcode_buf2xchar(const char* buf, size_t buf_size) {
	xmlChar* out;
	int outlen;
	int error;
#ifndef NDEBUG
	int saved_outlen;
#endif
	if(xmlCharEncodingInputFunc input=transcoder(FNAME).input) {
		outlen=buf_size*6;
#ifndef NDEBUG
		saved_outlen=outlen;
#endif
		out=(xmlChar*)xmlMalloc(outlen+1);
		error=input(
			out, &outlen,
			(const unsigned char*)buf, (int*)&buf_size
#ifdef PA_PATCHED_LIBXML_BACKWARD
			,0
#endif
			);
	} else {
		outlen=buf_size;
#ifndef NDEBUG
		saved_outlen=outlen;
#endif
		out=(xmlChar*)xmlMalloc(outlen+1);
		memcpy(out, buf, outlen);
		error=0;
	}

	if(error<0)
		throw Exception(0,
			0,
			"transcode_buf failed (%d)", error);

	assert(outlen<=saved_outlen); out[outlen]=0;
	return out;
}
