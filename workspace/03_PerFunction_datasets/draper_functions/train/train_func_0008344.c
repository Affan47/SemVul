charset_conversion(struct dvb_v5_fe_parms *parms, char **dest, const unsigned char *s,
			       size_t len,
			       char *type, char *output_charset)
{
	char *p = *dest;
	unsigned char *tmp;
	size_t destlen = len * 3;
	int need_conversion = 1;

	if (!strcasecmp(type, "ISO-6937")) {
		unsigned char *p1, *p2;


		for (p1 = (unsigned char *)s; p1 < s + len; p1++)
			for (p2 = en300468_latin_00_to_utf8[*p1].data;
			     p2 < en300468_latin_00_to_utf8[*p1].data + en300468_latin_00_to_utf8[*p1].len;
			     p2++)
				*p++ = *p2;
		*p = '\0';


		if (strcasecmp(output_charset, "UTF-8")) {
			tmp = (unsigned char *)*dest;
			len = p - *dest;

			*dest = malloc(destlen + 1);
			type = "UTF-8";
			s = tmp;
		} else
			need_conversion = 0;

	}


	if (need_conversion) {
		char out_cs[strlen(output_charset) + 1 + sizeof(CS_OPTIONS)];

		p = *dest;
		strcpy(out_cs, output_charset);
		strcat(out_cs, CS_OPTIONS);

		iconv_t cd = iconv_open(out_cs, type);
		if (cd == (iconv_t)(-1)) {
			memcpy(p, s, len);
			p[len] = '\0';
			dvb_logerr("Conversion from %s to %s not supported\n",
				 type, output_charset);
		} else {
			iconv(cd, (ICONV_CONST char **)&s, &len, &p, &destlen);
			iconv_close(cd);
			*p = '\0';
		}
	}
}
