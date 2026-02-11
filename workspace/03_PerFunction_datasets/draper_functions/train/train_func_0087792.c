ptabrect(P *org, long int height, long int right)
{
	P *p = pdup(org, USTR "ptabrect");

	while (height--) {
		int c;

		pcol(p, org->xcol);
		while ((c = pgetc(p)) != NO_MORE_DATA && c != '\n') {
			if (c == '\t') {
				prm(p);
				return '\t';
			} else if (piscol(p) > right)
				break;
		}
		if (c != '\n')
			pnextl(p);
	}
	prm(p);
	return ' ';
}
