add_space(GString *str)
{
	char c;

	if (str->len == 0)
		return;

	c = str->str[str->len - 1];
	if (c != ' ' && c != '\n')
		g_string_append_c(str, ' ');
}
