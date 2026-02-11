re_indent(incr)
int	incr;
{
	LinePtr	l1, l2, lp;
	int	c1, c2;
	Mark	*m = CurMark();
	Bufpos	savedot;

	DOTsave(&savedot);
	l1 = curline;
	c1 = curchar;
	l2 = m->m_line;
	c2 = m->m_char;
	(void) fixorder(&l1, &c1, &l2, &c2);
	for (lp = l1; lp != l2->l_next; lp = lp->l_next) {
		int	indent;

		SetLine(lp);
		ToIndent();
		indent = calc_pos(linebuf, curchar);
		if (indent != 0 || linebuf[0] != '\0')
			n_indent(indent + incr);
	}
	SetDot(&savedot);
}
