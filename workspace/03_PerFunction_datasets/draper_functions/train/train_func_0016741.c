build_complete_regexp(gchar **strings)
{
	int i = 0;
	gchar *expr = NULL;
	while (strings && strings[i] && *strings[i]) {
		int old_len = expr ? strlen(expr):0;
		int new_len = 0;
		gchar *tmpstr = NULL;

		if (g_utf8_validate(strings[i], -1, NULL))
			tmpstr = g_strdup(strings[i]);
		else
			tmpstr = conv_codeset_strdup(strings[i],
					conv_get_locale_charset_str_no_utf8(),
				 	CS_INTERNAL);

		if (strstr(tmpstr, "\n"))
			*(strstr(tmpstr, "\n")) = '\0';

		new_len = strlen(tmpstr);

		expr = g_realloc(expr,
			expr ? (old_len + strlen("|()") + new_len + 1)
			     : (strlen("()") + new_len + 1));

		if (old_len) {
			strcpy(expr + old_len, "|(");
			strcpy(expr + old_len + 2, tmpstr);
			strcpy(expr + old_len + 2 + new_len, ")");
		} else {
			strcpy(expr+old_len, "(");
			strcpy(expr+old_len + 1, tmpstr);
			strcpy(expr+old_len + 1 + new_len, ")");
		}
		g_free(tmpstr);
		i++;
	}
	return expr;
}
