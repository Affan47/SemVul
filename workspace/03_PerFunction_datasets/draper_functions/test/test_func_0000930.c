state(int c)
{
	Item *p1, *p2, *k, *l, *q1, *q2;
	int size1, size2, i;

	p1 = pstate[nstate];
	p2 = pstate[nstate+1];
	if(p1 == p2)
		return 0;

	for(k = p2-1; k > p1; k--)
		for(l = k-1; l >= p1; --l)
			if(l->pitem > k->pitem) {
				int *s;
				Lkset *ss;

				s = k->pitem;
				k->pitem = l->pitem;
				l->pitem = s;
				ss = k->look;
				k->look = l->look;
				l->look = ss;
			}
	size1 = p2 - p1;

	for(i = (c>=NTBASE)? ntstates[c-NTBASE]: tstates[c]; i != 0; i = mstates[i]) {

		q1 = pstate[i];
		q2 = pstate[i+1];
		size2 = q2 - q1;
		if(size1 != size2)
			continue;
		k = p1;
		for(l = q1; l < q2; l++) {
			if(l->pitem != k->pitem)
				break;
			k++;
		}
		if(l != q2)
			continue;

		pstate[nstate+1] = pstate[nstate];

		if(nolook)
			return i;
		for(l = q1, k = p1; l < q2; ++l, ++k ) {
			int s;

			SETLOOP(s)
				clset.lset[s] = l->look->lset[s];
			if(setunion(clset.lset, k->look->lset)) {
				tystate[i] = MUSTDO;

				l->look = flset( &clset );
			}
		}
		return i;
	}

	if(nolook)
		error("yacc state/nolook error");
	pstate[nstate+2] = p2;
	if(nstate+1 >= NSTATES)
		error("too many states");
	if(c >= NTBASE) {
		mstates[nstate] = ntstates[c-NTBASE];
		ntstates[c-NTBASE] = nstate;
	} else {
		mstates[nstate] = tstates[c];
		tstates[c] = nstate;
	}
	tystate[nstate] = MUSTDO;
	return nstate++;
}
