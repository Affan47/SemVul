str_find_char(const char* s, int ch1) {
	while (*s != 0) {
		if (*s == ch1) return s;
		s++;
	}
	return s;
}
