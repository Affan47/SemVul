peop(P *p)
{
	long indent;
	long prelen;

	if (!pnextl(p) || pisnpara(p) || (within && markk && p->byte >= markk->byte))
		return p;
	indent = nindent(p);
	prelen = prefix(p);
	while (pnextl(p) && (!within || !markk || p->byte < markk->byte)) {
		long ind = nindent(p);
		long len = prefix(p);

		if (ind != indent || len != prelen || pisnpara(p))
			break;
	}
	return p;
}
