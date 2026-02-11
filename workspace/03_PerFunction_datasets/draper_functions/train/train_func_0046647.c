split(char*& s, char c) {
	char *t = s;
	if (s && (s = strchr(s, c)) != NULL)
		* s++ = '\0';
	return t;
}
