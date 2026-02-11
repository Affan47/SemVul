extract_rfc2047_encoded_word (const gchar **in,
                              gchar **word)
{
	const gchar *inptr = *in, *start;

	header_decode_lwsp (&inptr);
	start = inptr;

	if (!strncmp (inptr, "=?", 2)) {
		inptr += 2;


		while (*inptr && *inptr != '?') {
			inptr++;
		}


		if (inptr[0] != '?' || !strchr ("BbQq", inptr[1]) || !inptr[1] || inptr[2] != '?')
			return FALSE;

		inptr += 3;


		while (*inptr && strncmp (inptr, "?=", 2) != 0) {
			inptr++;
		}

		if (!strncmp (inptr, "?=", 2)) {
			inptr += 2;

			*in = inptr;
			*word = g_strndup (start, inptr - start);

			return TRUE;
		}
	}

	return FALSE;
}
