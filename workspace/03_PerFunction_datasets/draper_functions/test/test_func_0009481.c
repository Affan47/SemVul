g_mime_encoding_uuencode_close (const unsigned char *inbuf, size_t inlen, unsigned char *outbuf, unsigned char *uubuf, int *state, guint32 *save)
{
	register unsigned char *outptr, *bufptr;
	register guint32 saved;
	int uulen, uufill, i;

	outptr = outbuf;

	if (inlen > 0)
		outptr += g_mime_encoding_uuencode_step (inbuf, inlen, outbuf, uubuf, state, save);

	uufill = 0;

	saved = *save;
	i = *state & 0xff;
	uulen = (*state >> 8) & 0xff;

	bufptr = uubuf + ((uulen / 3) * 4);

	if (i > 0) {
		while (i < 3) {
			saved <<= 8;
			uufill++;
			i++;
		}

		if (i == 3) {

			unsigned char b0, b1, b2;

			b0 = (saved >> 16) & 0xff;
			b1 = (saved >> 8) & 0xff;
			b2 = saved & 0xff;

			*bufptr++ = GMIME_UUENCODE_CHAR ((b0 >> 2) & 0x3f);
			*bufptr++ = GMIME_UUENCODE_CHAR (((b0 << 4) | ((b1 >> 4) & 0xf)) & 0x3f);
			*bufptr++ = GMIME_UUENCODE_CHAR (((b1 << 2) | ((b2 >> 6) & 0x3)) & 0x3f);
			*bufptr++ = GMIME_UUENCODE_CHAR (b2 & 0x3f);

			uulen += 3;
			saved = 0;
			i = 0;
		}
	}

	if (uulen > 0) {
		int cplen = ((uulen / 3) * 4);

		*outptr++ = GMIME_UUENCODE_CHAR ((uulen - uufill) & 0xff);
		memcpy (outptr, uubuf, cplen);
		outptr += cplen;
		*outptr++ = '\n';
		uulen = 0;
	}

	*outptr++ = GMIME_UUENCODE_CHAR (uulen & 0xff);
	*outptr++ = '\n';

	*save = 0;
	*state = 0;

	return (outptr - outbuf);
}
