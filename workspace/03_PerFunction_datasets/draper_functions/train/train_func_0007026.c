base64_encode(gchar *out, const guchar *in, gint inlen)
{
	const guchar *inp = in;
	gchar *outp = out;

	while (inlen >= 3) {
		*outp++ = base64char[(inp[0] >> 2) & 0x3f];
		*outp++ = base64char[((inp[0] & 0x03) << 4) |
				     ((inp[1] >> 4) & 0x0f)];
		*outp++ = base64char[((inp[1] & 0x0f) << 2) |
				     ((inp[2] >> 6) & 0x03)];
		*outp++ = base64char[inp[2] & 0x3f];

		inp += 3;
		inlen -= 3;
	}

	if (inlen > 0) {
		*outp++ = base64char[(inp[0] >> 2) & 0x3f];
		if (inlen == 1) {
			*outp++ = base64char[(inp[0] & 0x03) << 4];
			*outp++ = '=';
		} else {
			*outp++ = base64char[((inp[0] & 0x03) << 4) |
					     ((inp[1] >> 4) & 0x0f)];
			*outp++ = base64char[((inp[1] & 0x0f) << 2)];
		}
		*outp++ = '=';
	}

	*outp = '\0';
}
