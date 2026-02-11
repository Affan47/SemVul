_next_tok (char *sep, char **str)
{
	char *tok;


	while ((**str != '\0') && (strchr(sep, **str) != '\0'))
		(*str)++;

	if (**str == '\0')
		return NULL;


	tok = *str;


	while ((**str != '\0') && (strchr(sep, **str) == '\0'))
		(*str)++;


	while ((**str != '\0') && (strchr(sep, **str) != '\0'))
		*(*str)++ = '\0';

	return (tok);
}
