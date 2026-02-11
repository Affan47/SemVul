m_quote_capture(char **str, int start, int end)
{
    int i, e;
    char *s;

    e = token[end].start_index + token[end].length - 1;
    *str = gp_realloc(*str, (e - token[start].start_index + 1), "string");
    s = *str;
    for (i = token[start].start_index + 1; i < e && gp_input_line[i] != NUL; i++)
	*s++ = gp_input_line[i];
    *s = NUL;

    if (gp_input_line[token[start].start_index] == '"')
	parse_esc(*str);
    else
	parse_sq(*str);

}
