str_find(const char *string, int c, int nocase)
{
	if (nocase) {

		c = utf8_upper(c);
	}
	while (*string) {
		int ch;
		int n = reg_utf8_tounicode_case(string, &ch, nocase);
		if (c == ch) {
			return string;
		}
		string += n;
	}
	return NULL;
}
