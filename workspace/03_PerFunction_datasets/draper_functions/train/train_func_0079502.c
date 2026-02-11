print_lower_len(const char *str, int len)
{
	int i;

	for (i = 0; i < len; i++)
		FORM_print_char(tolower(str[i]));
}
