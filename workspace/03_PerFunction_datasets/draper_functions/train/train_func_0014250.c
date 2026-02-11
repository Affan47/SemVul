writem(int *pp)
{
	int i,*p;
	static char sarr[ISIZE];
	char* q;

	for(p=pp; *p>0; p++)
		;
	p = prdptr[-*p];
	q = chcopy(sarr, nontrst[*p-NTBASE].name);
	q = chcopy(q, ": ");
	for(;;) {
		*q = ' ';
		p++;
		if(p == pp)
			*q = '.';
		q++;
		*q = '\0';
		i = *p;
		if(i <= 0)
			break;
		q = chcopy(q, symnam(i));
		if(q > &sarr[ISIZE-30])
			error("item too big");
	}


	i = *pp;
	if(i < 0 ) {
		q = chcopy(q, "    (");
		sprint(q, "%d)", -i);
	}
	return sarr;
}
