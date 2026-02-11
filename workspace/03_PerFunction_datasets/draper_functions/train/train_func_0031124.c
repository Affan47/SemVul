f_prep(pat_index, Pattern)
uchar *Pattern;   int pat_index;
{
int i, m;
register unsigned hash=0;
#ifdef debug
	puts(Pattern);
#endif
	m = p_size;
		for (i=m-1; i>=(1+LONG); i--) {
				hash = (tr1[Pattern[i]]);
				hash = (hash << Hbits) + (tr1[Pattern[i-1]]);
		if(LONG) hash = (hash << Hbits) + (tr1[Pattern[i-2]] );
		if(SHIFT1[hash] >= m-1-i) SHIFT1[hash] = m-1-i;
	}
	i=m-1;
		hash = (tr1[Pattern[i]]);
		hash = (hash << Hbits) + (tr1[Pattern[i-1]]);
	if(LONG) hash = (hash << Hbits) + (tr1[Pattern[i-2]] );
		if(SHORT) hash=tr[Pattern[0]];
#ifdef debug
	printf("hash = %d\n", hash);
#endif
		HASH[hash]++;
		return;
}
