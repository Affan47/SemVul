man_codepara(FILE *fp, word *text, int charset) {
    fprintf(fp, ".nf\n");
    for (; text; text = text->next) if (text->type == word_WeakCode) {
	char *c;
	wchar_t *t, *e;
	int quote_props = QUOTE_INITCTRL | QUOTE_LITERAL;

	t = text->text;
	if (text->next && text->next->type == word_Emph) {
	    e = text->next->text;
	    text = text->next;
	} else
	    e = NULL;

	while (e && *e && *t) {
	    int n;
	    int ec = *e;

	    for (n = 0; t[n] && e[n] && e[n] == ec; n++);
	    if (ec == 'i')
		fprintf(fp, "\\fI");
	    else if (ec == 'b')
		fprintf(fp, "\\fB");
	    man_convert(t, n, &c, quote_props, charset, NULL);
	    quote_props &= ~QUOTE_INITCTRL;
	    fprintf(fp, "%s", c);
	    sfree(c);
	    if (ec == 'i' || ec == 'b')
		fprintf(fp, "\\fP");
	    t += n;
	    e += n;
	}
	man_convert(t, 0, &c, quote_props, charset, NULL);
	fprintf(fp, "%s\n", c);
	sfree(c);
    }
    fprintf(fp, ".fi\n");
}
