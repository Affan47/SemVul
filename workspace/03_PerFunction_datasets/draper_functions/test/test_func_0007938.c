quoted_decode (const unsigned char *in, size_t len, unsigned char *out, int *state, guint32 *save)
{
	register const unsigned char *inptr;
	register unsigned char *outptr;
	const unsigned char *inend;
	unsigned char c, c1;
	guint32 saved;
	int need;

	if (len == 0)
		return 0;

	inend = in + len;
	outptr = out;
	inptr = in;

	need = *state;
	saved = *save;

	if (need > 0) {
		if (isxdigit ((int) *inptr)) {
			if (need == 1) {
				c = g_ascii_toupper ((int) (saved & 0xff));
				c1 = g_ascii_toupper ((int) *inptr++);
				saved = 0;
				need = 0;

				goto decode;
			}

			saved = 0;
			need = 0;

			goto equals;
		}


		*outptr++ = '=';

		if (need == 1)
			*outptr++ = (char) (saved & 0xff);

		saved = 0;
		need = 0;
	}

	while (inptr < inend) {
		c = *inptr++;
		if (c == '=') {
		equals:
			if (inend - inptr >= 2) {
				if (isxdigit ((int) inptr[0]) && isxdigit ((int) inptr[1])) {
					c = g_ascii_toupper (*inptr++);
					c1 = g_ascii_toupper (*inptr++);
				decode:
					*outptr++ = (((c >= 'A' ? c - 'A' + 10 : c - '0') & 0x0f) << 4)
						| ((c1 >= 'A' ? c1 - 'A' + 10 : c1 - '0') & 0x0f);
				} else {

					*outptr++ = '=';
				}
			} else {

				if (inptr < inend) {
					if (isxdigit ((int) *inptr)) {
						saved = *inptr;
						need = 1;
						break;
					} else {

						*outptr++ = '=';
					}
				} else {
					saved = 0;
					need = 2;
					break;
				}
			}
		} else if (c == '_') {

			*outptr++ = ' ';
		} else {
			*outptr++ = c;
		}
	}

	*state = need;
	*save = saved;

	return (size_t) (outptr - out);
}
