mark_symbol()
{
    register int c;
    register bucket *bp;

    c = cptr[1];
    if (c == '%' || c == '\\')
    {
	cptr += 2;
	return (1);
    }

    if (c == '=')
	cptr += 2;
    else if ((c == 'p' || c == 'P') &&
	     ((c = cptr[2]) == 'r' || c == 'R') &&
	     ((c = cptr[3]) == 'e' || c == 'E') &&
	     ((c = cptr[4]) == 'c' || c == 'C') &&
	     ((c = cptr[5], !IS_IDENT(c))))
	cptr += 5;
    else
	syntax_error(lineno, line, cptr);

    c = nextc();
    if (isalpha(c) || c == '_' || c == '.' || c == '$')
	bp = get_name();
    else if (c == '\'' || c == '"')
	bp = get_literal();
    else
    {
	syntax_error(lineno, line, cptr);

    }

    if (rprec[nrules] != UNDEFINED && bp->prec != rprec[nrules])
	prec_redeclared();

    rprec[nrules] = bp->prec;
    rassoc[nrules] = bp->assoc;
    return (0);
}
