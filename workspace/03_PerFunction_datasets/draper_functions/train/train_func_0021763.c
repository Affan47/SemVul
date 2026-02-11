purge_quoted_commas (char *s)
{
    int inquote = 0;

    while (*s) {
	if (*s == '"') {
	    inquote = !inquote;
	} else if (inquote && *s == ',') {
	    *s = ' ';
	}
	s++;
    }
}
