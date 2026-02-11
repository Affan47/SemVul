gdome_utf16Length (xmlChar *utf8str) {
	gulong len = 0L, i;
	char c;

	for (i = 0L; (c = utf8str[i]) != '\0'; i++)
		if ((c & 0xf8) == 0xf0)
			len += 2L;
		else if ((c & 0xc0) != 0x80)
			len++;

	return len;
}
