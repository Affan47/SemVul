upload_416_extra(char *buf, size_t size, void *arg, uint32 unused_flags)
{
	const struct upload_http_cb *a = arg;
	const struct upload *u = a->u;
	size_t len;
	char fsize[UINT64_DEC_BUFLEN];

	(void) unused_flags;
	upload_check(u);

	uint64_to_string_buf(u->file_size, fsize, sizeof fsize);
	len = concat_strings(buf, size,
			"Content-Range: bytes */", fsize, (void *) 0);

	if (len >= size && GNET_PROPERTY(upload_debug)) {
		g_warning("U/L cannot send Content-Range header back: "
			"only %u byte%s left",
			(unsigned) size, 1 == size ? "" : "s");
	}


	return len < size ? len : 0;
}
