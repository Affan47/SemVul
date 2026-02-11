url_addrspec_end (const char *in, const char *pos, const char *inend, urlmatch_t *match)
{
	const char *inptr = pos;
	int parts = 0, digits;
	gboolean got_dot = FALSE;

	g_assert (*inptr == '@');

	inptr++;

	if (*inptr == '[') {

		do {
			inptr++;

			digits = 0;
			while (inptr < inend && is_digit (*inptr) && digits < 3) {
				inptr++;
				digits++;
			}

			parts++;

			if (*inptr != '.' && parts != 4)
				return FALSE;
		} while (parts < 4);

		if (inptr < inend && *inptr == ']')
			inptr++;
		else
			return FALSE;

		got_dot = TRUE;
	} else {
		while (inptr < inend) {
			if (is_domain (*inptr))
				inptr++;
			else
				break;

			while (inptr < inend && is_domain (*inptr))
				inptr++;

			if (inptr < inend && *inptr == '.' && is_domain (inptr[1])) {
				if (*inptr == '.')
					got_dot = TRUE;
				inptr++;
			}
		}
	}

	if (inptr == pos + 1 || !got_dot)
		return FALSE;

	match->um_eo = (inptr - in);

	return TRUE;
}
