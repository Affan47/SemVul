ast_replace_subargument_delimiter(char *s)
{
	for (; *s; s++) {
		if (*s == '^') {
			*s = ',';
		}
	}
}
