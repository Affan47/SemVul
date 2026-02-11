isWordCdata(unsigned int start, unsigned int end, Accessor &styler) {
	char s[30 + 1];
	unsigned int i = 0;
	for (; i < end - start + 1 && i < 30; i++) {
		s[i] = styler[start + i];
	}
	s[i] = '\0';
	return (0 == strcmp(s, "[CDATA["));
}
