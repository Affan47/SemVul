tok_get()
{
    register struct token *t;
    register int c;
    int     d;


    t = tok_alloc();

    for (;;) {
	if ((INPUT(c)) == EOF) {
	    tok_free(t);
	    return (0);
	} else if ((t->line = in_line, t->path = in_path), !isascii(c)) {
	    t->vstr->str[0] = c;
	    t->vstr->str[1] = 0;
	    t->tokno = TOK_OTHER;
	    break;
	} else if (ISSPACE(c)) {
	    COLLECT(t->vstr, c, ISSPACE(c));
	    t->tokno = TOK_WSPACE;
	    break;
	} else if (ISALPHA(c)) {
	    COLLECT(t->vstr, c, ISALNUM(c));
	    t->tokno = TOK_WORD;
	    break;
	} else if (isdigit(c)) {
	    COLLECT(t->vstr, c, isdigit(c));
	    t->tokno = TOK_NUMBER;
	    break;
	} else if (c == '"' || c == '\'') {
	    t->tokno = read_quoted(t->vstr, c);
	    break;
	} else if (ISDOT(c)) {
	    COLLECT(t->vstr, c, ISDOT(c));
	    t->tokno = TOK_OTHER;
	    break;
	} else if (c == '#' && last_tokno == '\n') {
	    do_control();
	    continue;
	} else {
	    t->vstr->str[0] = c;
	    if (c == '\n') {
		in_line++;
		if (nl_compensate > 0) {
		    UNPUT('\n');
		    nl_compensate--;
		}
	    } else if (c == '/') {
		if ((INPUT(d)) == '*') {
		    t->vstr->str[1] = d;
		    read_comment(t->vstr);
		    t->tokno = TOK_WSPACE;
		    break;
		} else {
		    if (d != EOF)
			UNPUT(d);
		}
	    } else if (c == '\\') {
		t->vstr->str[1] = (INPUT(c) == EOF ? 0 : c);
		t->vstr->str[2] = 0;
		t->tokno = TOK_OTHER;
		break;
	    }
	    t->vstr->str[1] = 0;
	    t->tokno = c;
	    break;
	}
    }
    last_tokno = t->tokno;
    t->end_line = in_line;
    return (t);
}
