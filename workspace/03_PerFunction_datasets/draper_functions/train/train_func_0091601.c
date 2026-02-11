linkify(const char *input)
{
	int i = 0;
	int len = strlen(input);
	char *result;
	GString *temp_result;
	GString *temp = NULL;

	temp_result = g_string_sized_new(2048);

	while (i < len) {
		if (isspace(input[i])) {
			g_string_append_c(temp_result, input[i]);
			i++;
		} else {
			temp = get_next_token(input + i);
			eb_debug(DBG_HTML, "%s\t%s\t%d\t%d\n", input, input + i,
				i, temp->len);
			i += temp->len;
			linkify_token(temp);
			g_string_append(temp_result, temp->str);
			g_string_free(temp, TRUE);
		}
	}

	result = temp_result->str;
	g_string_free(temp_result, FALSE);
	return result;
}
