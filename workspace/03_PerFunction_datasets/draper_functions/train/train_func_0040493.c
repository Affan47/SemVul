soundexify (const gchar *sound,
            gchar code[5])
{
	guchar *c, last = '\0';
	gint n;

	for (c = (guchar *) sound; *c && !isalpha (*c); c++);
	code[0] = toupper (*c);
	memset (code + 1, 0, 3);
	for (n = 1; *c && n < 5; c++) {
		guchar ch = soundex_table[*c];

		if (ch && ch != last) {
			code[n++] = ch;
			last = ch;
		}
	}
	code[4] = '\0';
}
