copy_text()
{
    register int c;
    register FILE *f = text_file;
    int need_newline = 0;
    int t_lineno = lineno;
    char *t_line = dup_line();
    char *t_cptr = t_line + (cptr - line - 2);

    if (*cptr == '\n') {
	if (get_line() == 0)
	    unterminated_text(t_lineno, t_line, t_cptr); }
    if (!lflag) fprintf(f, line_format, lineno, (inc_file?inc_file_name:input_file_name));
loop:
    switch (c = *cptr++) {
    case '\n':
	putc('\n', f);
	need_newline = 0;
	if (get_line()) goto loop;
	unterminated_text(t_lineno, t_line, t_cptr);
    case '\'':
    case '"':
	putc(c, f);
	copy_string(c, f, 0);
	need_newline = 1;
	goto loop;
    case '/':
	putc(c, f);
	copy_comment(f, 0);
	need_newline = 1;
	goto loop;
    case '%':
    case '\\':
	if (*cptr == '}') {
	    if (need_newline) putc('\n', f);
	    ++cptr;
	    FREE(t_line);
	    return; }

    default:
	putc(c, f);
	need_newline = 1;
	goto loop; }
}
