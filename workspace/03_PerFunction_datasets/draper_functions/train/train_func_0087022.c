GetRange(unsigned int start, unsigned int end, Accessor &styler, char *s, unsigned int len) {
	unsigned int i = 0;
	while ((i < end - start + 1) && (i < len-1)) {
		s[i] = static_cast<char>(styler[start + i]);
		i++;
	}
	s[i] = '\0';
}
