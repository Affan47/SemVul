unescape(const char *src) {
	int state = 0;
	string_t buf;
	unsigned char hex_msb = 0;

	if (!src)
		return NULL;

	buf = string_init(NULL);

	for (; *src; src++) {
		char ch = *src;

		if (state == 0) {


			if (ch == '\\' && *(src + 1)) {
				state = 1;
				continue;
			}
			string_append_c(buf, ch);
		} else if (state == 1) {
			if (ch == 'a')
				ch = '\a';
			else if (ch == 'b')
				ch = '\b';
			else if (ch == 't')
				ch = '\t';
			else if (ch == 'n')
				ch = '\n';
			else if (ch == 'v')
				ch = '\v';
			else if (ch == 'f')
				ch = '\f';
			else if (ch == 'r')
				ch = '\r';
			else if (ch == 'x' && *(src + 1) && *(src + 2)) {
				state = 2;
				continue;
			} else if (ch != '\\')
				string_append_c(buf, '\\');
			string_append_c(buf, ch);
			state = 0;
		} else if (state == 2) {
			hex_msb = ch;
			state = 3;
		} else if (state == 3) {
#define unhex(x) (unsigned char) ((x >= '0' && x <= '9') ? (x - '0') : \
	(x >= 'A' && x <= 'F') ? (x - 'A' + 10) : \
	(x >= 'a' && x <= 'f') ? (x - 'a' + 10) : 0)
			string_append_c(buf, unhex(ch) | (unhex(hex_msb) << 4));
#undef unhex
			state = 0;
		}
	}

	return string_free(buf, 0);
}
