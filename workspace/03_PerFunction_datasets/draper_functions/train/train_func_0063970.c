pisnpara(P *p)
{
	P *q;
	int c;

	q = pdup(p);
	p_goto_bol(q);
	while (cpara(c = pgetc(q)))
		;
	prm(q);
	if (c == '.' || c == '\r' || c == '\n')
		return 1;
	else
		return 0;
}
