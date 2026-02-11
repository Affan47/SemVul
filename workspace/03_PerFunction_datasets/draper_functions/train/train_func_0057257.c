gdome_utf16Offset (xmlChar *utf8str, gulong utf16offset, gulong *utf8offset) {
	gulong len = 0L, i;
	char c;

	for (i = 0L; len < utf16offset && (c = utf8str[i]) != '\0'; i++)
		if ((c & 0xf8) == 0xf0)
			len += 2L;
		else if ((c & 0xc0) != 0x80)
			len++;

	for (;(utf8str[i] & 0xc0) == 0x80; i++);

	*utf8offset = i;

	if (len == utf16offset )
		return TRUE;
	else
		return FALSE;
}
