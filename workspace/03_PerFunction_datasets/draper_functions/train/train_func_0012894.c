append(int (*f)(void), int *a)
{
	int *a1, *a2, *rdot, nline, d;

	nline = 0;
	dot = a;
	while((*f)() == 0) {
		if((dol-zero) >= nlall) {
			nlall += 512;
			a1 = realloc(zero, (nlall+50)*sizeof(int*));
			if(a1 == 0) {
				error("MEM?");
				rescue();
			}

			d = addr1 - zero;
			addr1 = a1 + d;
			d = addr2 - zero;
			addr2 = a1 + d;
			d = dol - zero;
			dol = a1 + d;
			d = dot - zero;
			dot = a1 + d;
			zero = a1;
		}
		d = putline();
		nline++;
		a1 = ++dol;
		a2 = a1+1;
		rdot = ++dot;
		while(a1 > rdot)
			*--a2 = *--a1;
		*rdot = d;
	}
	return nline;
}
