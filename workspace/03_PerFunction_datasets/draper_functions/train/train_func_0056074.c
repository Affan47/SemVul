parser_getc (parser *p)
{
#if EDEBUG > 1
    fprintf(stderr, "parser_getc: src='%s'\n", p->point);
#endif

    p->ch = 0;

    if (more_input(p->point)) {
	p->ch = *p->point;
	p->point += 1;
    }

#if EDEBUG > 1
    if (p->ch) {
	fprintf(stderr, "parser_getc: returning '%c'\n", p->ch);
    }
#endif

    return p->ch;
}
