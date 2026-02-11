string_index_of_any(const char *str, const char *findchars)
{
	int c;
	for (c = 0; str[c] != '\0'; c++) {
		if (string_index_of_c(findchars, str[c]) != -1)
			return c;
	}
	return -1;
}
