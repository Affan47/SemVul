git_buf_put_base64(git_buf *buf, const char *data, size_t len)
{
	size_t extra = len % 3;
	uint8_t *write, a, b, c;
	const uint8_t *read = (const uint8_t *)data;

	ENSURE_SIZE(buf, buf->size + 4 * ((len / 3) + !!extra) + 1);
	write = (uint8_t *)&buf->ptr[buf->size];


	for (len -= extra; len > 0; len -= 3) {
		a = *read++;
		b = *read++;
		c = *read++;

		*write++ = b64str[a >> 2];
		*write++ = b64str[(a & 0x03) << 4 | b >> 4];
		*write++ = b64str[(b & 0x0f) << 2 | c >> 6];
		*write++ = b64str[c & 0x3f];
	}

	if (extra > 0) {
		a = *read++;
		b = (extra > 1) ? *read++ : 0;

		*write++ = b64str[a >> 2];
		*write++ = b64str[(a & 0x03) << 4 | b >> 4];
		*write++ = (extra > 1) ? b64str[(b & 0x0f) << 2] : '=';
		*write++ = '=';
	}

	buf->size = ((char *)write) - buf->ptr;
	buf->ptr[buf->size] = '\0';

	return 0;
}
