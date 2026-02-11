detect_charset_cylillic(const gchar *text)
{
	guint8 c = *text;
	gboolean noniso = FALSE;
	guint32 xc = 0, xd = 0, xef = 0;

	const gchar *charset = get_encoding_items(get_encoding_code())->item[OPENI18N];

	while ((c = *text++) != '\0') {
		if (c >= 0x80 && c <= 0x9F)
			noniso = TRUE;
		else if (c >= 0xC0 && c <= 0xCF)
			xc++;
		else if (c >= 0xD0 && c <= 0xDF)
			xd++;
		else if (c >= 0xE0)
			xef++;
	}

	if (!noniso && ((xc + xef) < xd))
		charset = "ISO-8859-5";
	else if ((xc + xd) < xef)
		charset = "CP1251";

	return charset;
}
