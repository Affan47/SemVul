xmp_new(const char *buffer, size_t len)
{
	CHECK_PTR(buffer, NULL);
	RESET_ERROR;

	SXMPMeta *txmp;
	try {
		txmp = new SXMPMeta(buffer, len);
	}
	catch(const XMP_Error & e) {
		set_error(e);
		txmp = 0;
	}
	return (XmpPtr)txmp;
}
