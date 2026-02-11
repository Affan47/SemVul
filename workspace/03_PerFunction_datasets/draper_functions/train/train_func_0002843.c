get_indent(lp)
register LinePtr	lp;
{
	Bufpos	save;
	register int	indent;

	bslash = NO;
	if (lp == NULL)
		return I_BUFEDGE;

	DOTsave(&save);
	SetLine(lp);
	if (LookingAt(ParaDelim, linebuf, 0)) {
		indent = I_DELIM;
		if (linebuf[0] == '\\' && REeom == 1) {


			bslash = YES;
			SetLine(lp->l_next);
			if (linebuf[0] != '\\')
				indent = 0;
		}
	} else {
		ToIndent();
		indent = calc_pos(linebuf, curchar);
	}
	SetDot(&save);

	return indent;
}
