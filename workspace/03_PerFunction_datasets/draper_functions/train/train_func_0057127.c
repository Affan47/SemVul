prep(Pattern, M, D)
CHARTYPE *Pattern;
register int M, D;
{
	register int i, j, k, p, shift;
	register unsigned m;
	unsigned hash, b_size = 3;
	m = M/(D+1);
	p = M - m*(D+1);
	for (i = 0; i < MAXSYM; i++) SHIFT[i] = m;
	for (i = M-1; i>=p ; i--) {
		shift = (M-1-i)%m;
		hash = Pattern[i];
		if((int)(SHIFT[hash]) > (int)(shift)) SHIFT[hash] = shift;
	}
#ifdef DEBUG
	for(i=0; i<M; i++) printf(" %d,", SHIFT[Pattern[i]]);
	printf("\n");
#endif
	shift_1 = m;
	for(i=0; i<D+1; i++) {
		j = M-1 - m*i;
		for(k=1; k<m; k++) {
			for(p=0; p<D+1; p++)
				if(Pattern[j-k] == Pattern[M-1-m*p])
					if(k < shift_1) shift_1 = k;
		}
	}
#ifdef DEBUG
	printf("\nshift_1 = %d", shift_1);
#endif
	if(shift_1 == 0) shift_1 = 1;
	for(i=0; i<MAXMEMBER; i++) MEMBER[i] = 0;
	if (m < 3) b_size = m;
	for(i=0; i<D+1; i++) {
		j = M-1 - m*i;
		hash = 0;
		for(k=0; k<b_size; k++) {
			hash = (hash << 2) + Pattern[j-k];
		}
#ifdef DEBUG
		printf(" hash = %d,", hash);
#endif
		MEMBER[hash] = 1;
	}
}
