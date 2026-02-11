e_vcard_qp_decode (const gchar *txt)
{
	const gchar *inptr;
	gchar *decoded, *outptr;

	if (!txt)
		return NULL;

	decoded = g_malloc (sizeof (gchar) * strlen (txt) + 1);

	outptr = decoded;

	for (inptr = txt; *inptr; inptr++) {
		gchar c = *inptr;

		if (c == '=' && (inptr[1] == '\r' || inptr[1] == '\n')) {

			if (inptr[2] == '\n')
				inptr++;
			inptr++;
			continue;
		}

		if (c == '=' && inptr[1] && inptr[2]) {
			guchar a = toupper (inptr[1]), b = toupper (inptr[2]);
			if (isxdigit (a) && isxdigit (b)) {
				*outptr++ = (((a >= 'A' ? a - 'A' + 10 : a - '0') & 0x0f) << 4)
					   | ((b >= 'A' ? b - 'A' + 10 : b - '0') & 0x0f);
			} else {
				*outptr++ = '=';
				*outptr++ = inptr[1];
				*outptr++ = inptr[2];
			}

			inptr += 2;
		} else {
			*outptr++ = *inptr;
		}
	}

	*outptr = '\0';

	return decoded;
}
