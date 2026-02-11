extract_initials(ARTICLE *art, char *buffer, int maxlen, int cap)
{
    char	*c;
    int		pos = 0;

    maxlen -= 4;
    if (art && art->from && (c = art->tree_data.label)) {
	if (res_show_number_lines())
	    c = skip_line_count(c);

	while (*c != '\0') {
	    while (*c != '\0' && !IS_ALPHA(*c))
		c++;
	    if (*c == '\0' || pos > maxlen)
		break;
	    buffer[pos++] = (cap && IS_LOWER(*c)) ? UPPER(*c) : *c;
	    while (*c != '\0' && IS_ALPHA(*c))
		c++;
	}
    }

    buffer[pos] = '\0';

    return pos;
}
