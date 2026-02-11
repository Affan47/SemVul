line_alignment(struct view *view, position_t lnstart0)
{
	position_t lnstart, offset, at, corr;
	Unicode_t ch;
	unsigned indent, brindent;
	unsigned tabstop = view->text->tabstop;
	Boolean_t is_nested;

	if (!lnstart0)
		return 0;
	lnstart = lnstart0 - 1;
	tabstop |= !tabstop;


again:	lnstart = find_line_start(view, lnstart);
	while (lnstart && view_char(view, lnstart, NULL) == '\n')
		lnstart = find_line_start(view, lnstart-1);


	at = lnstart;
	indent = current_line_indentation(view, &at);


	brindent = indent + 1;
	is_nested = FALSE;
	for (ch = view_char(view, at, &offset);
	     IS_UNICODE(ch) && ch != '\n';
	     ch = view_char(view, at = offset, &offset), brindent++) {
		switch (ch) {
		case '(':
		case '[':
			corr = find_corresponding_bracket(view, at);
			if (corr >= lnstart0) {
				indent = brindent;
				is_nested = TRUE;
			}
			break;
		case ')':
		case ']':
			corr = find_corresponding_bracket(view, at);
			if (corr < lnstart) {
				lnstart = corr;
				goto again;
			}
			break;
		case '\t':
			brindent = (brindent/tabstop + 1) * tabstop;
			break;
		}
	}


	if (!is_nested && lnstart0) {
		ch = view_char_prior(view, lnstart0 - 1, NULL);
		if (ch == '{' || ch == ')' || ch == ':' || ch == 'e')
			indent = (indent/tabstop + 1) * tabstop;
		else if (indent >= tabstop) {
			offset = lnstart;
			do ch = view_char_prior(view, offset, &offset);
			while (ch == ' ' || ch == '\t' || ch == '\n');
			if (ch == ')' )
				indent = (indent/tabstop - 1) * tabstop;
		}
	}


	if (indent) {
		offset = lnstart0;
		do ch = view_char(view, offset, &offset);
		while (ch == ' ' || ch == '\t');
		if (ch == '}')
			indent = (indent/tabstop - 1) * tabstop;
	}

	return indent;
}
