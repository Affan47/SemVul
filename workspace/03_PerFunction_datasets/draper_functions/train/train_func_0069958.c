crop_by_whitespace(gchar *string) {
	gchar *a, *b;

	for(b = string; *b; b++);
	for(; b > string && strchr(VALID_WHITESPACE, *(b - 1)); b--);
	*b = '\0';


	for(b = string; *b && strchr(VALID_WHITESPACE, *b); b++);
	for(a = string; *b; *a++ = *b++);
	*a = '\0';
}
