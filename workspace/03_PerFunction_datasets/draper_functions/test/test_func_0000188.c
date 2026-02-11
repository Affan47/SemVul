theme_format_append_variable(GString *str, const char **format)
{
	const char *orig;
	char *value, *args[1] = { NULL };
	int free_ret;

	orig = *format;
	(*format)++;

	value = parse_special((char **) format, NULL, NULL,
			      args, &free_ret, NULL, PARSE_FLAG_ONLY_ARGS);
	if (free_ret) g_free(value);

	if (**format != '\0')
		(*format)++;


	value = g_strndup(orig, (int) (*format-orig));
	g_string_append(str, value);
	g_free(value);
}
