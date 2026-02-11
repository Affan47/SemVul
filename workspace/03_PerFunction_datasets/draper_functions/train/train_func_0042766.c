escape(const char *src) {
	static const char esc[] = "\r\n";
	string_t dst;

	if (!src)
		return NULL;

	dst = string_init(NULL);

	for (; *src; src++) {
		char ch = *src;
		static const char esctab[] = "abtnvfr";

		if (!(ch == '\\' || strchr(esc, ch))) {
			string_append_c(dst, ch);
			continue;
		}

		string_append_c(dst, '\\');

		if (ch >= 0x07 && ch <= 0x0D)
			string_append_c(dst, esctab[ch - 0x07]);
		else if (ch == '\\')
			string_append_c(dst, '\\');
		else {
			char s[5];
			snprintf(s, sizeof(s), "x%02X", (unsigned char) ch);
			string_append(dst, s);
		}
	}

	return string_free(dst, 0);
}
