maexec(struct macro *mp)
{
	struct line	*lp;
	const char	*sp;
	char	*copy, *cp;
	int	r = 0;

	unset_allow_undefined = 1;
	for (lp = mp->ma_contents; lp; lp = lp->l_next) {
		sp = lp->l_line;
		while (sp < &lp->l_line[lp->l_linesize] &&
				(blankchar(*sp&0377) || *sp == '\n' ||
				 *sp == '\0'))
			sp++;
		if (sp == &lp->l_line[lp->l_linesize])
			continue;
		cp = copy = smalloc(lp->l_linesize + (lp->l_line - sp));
		do
			*cp++ = *sp != '\n' ? *sp : ' ';
		while (++sp < &lp->l_line[lp->l_linesize]);
		r = execute(copy, 0, lp->l_linesize);
		free(copy);
	}
	unset_allow_undefined = 0;
	return r;
}
