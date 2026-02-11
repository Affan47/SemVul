lastline(lp)
register LinePtr	lp;
{
	register LinePtr	next;

	while ((next = lp->l_next) != NULL)
		lp = next;
	return lp;
}
