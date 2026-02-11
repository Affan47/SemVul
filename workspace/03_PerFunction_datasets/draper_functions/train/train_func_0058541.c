copy_string(int quote, FILE *f1, FILE *f2)
{
register int	c;
int		s_lineno = lineno;
char		*s_line = dup_line();
char		*s_cptr = s_line + (cptr - line - 1);

    for (;;) {
	OUTC(c = *cptr++);
	if (c == quote) {
	    FREE(s_line);
	    return; }
	if (c == '\n')
	    unterminated_string(s_lineno, s_line, s_cptr);
	if (c == '\\') {
	    OUTC(c = *cptr++);
	    if (c == '\n') {
		if (get_line() == 0)
		    unterminated_string(s_lineno, s_line, s_cptr); } } }
}
