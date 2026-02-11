StrUpr(char *s) {
	while (*s) {
		*s = MakeUpperCase(*s);
		s++;
	}
}
