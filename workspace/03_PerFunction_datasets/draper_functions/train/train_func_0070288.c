line_has_quote_char(const gchar * str, const gchar *quote_chars)
{
	gchar * position = NULL;
	gchar * tmp_pos = NULL;
	int i;

	if (quote_chars == NULL)
		return FALSE;

	for (i = 0; i < strlen(quote_chars); i++) {
		tmp_pos = strchr (str,	quote_chars[i]);
		if(position == NULL
		   || (tmp_pos != NULL && position >= tmp_pos) )
			position = tmp_pos;
	}
	return position;
}
