prep4(Pattern, m)
char *Pattern;
int m;
{
	int i, j, k;
	unsigned hash;

	for(i=0; i< MAXSYM; i++) char_map[i] = 0;
	char_map['a'] = char_map['A'] = 4;
	char_map['g'] = char_map['g'] = 1;
	char_map['t'] = char_map['t'] = 2;
	char_map['c'] = char_map['c'] = 3;
	char_map['n'] = char_map['n'] = 5;

	BSize = blog(4, m);
	for (i = 1, Hashmask = 1 ; i<(int)(BSize*LOG_DNA); i++) Hashmask = (Hashmask << 1) + 1 ;
	if (MEMBER_D != NULL) free(MEMBER_D);
	MEMBER_D = (char *) malloc((Hashmask+1)  * sizeof(char));
#ifdef DEBUG
	printf("BSize = %d", BSize);
#endif
	for (i=0; i <= Hashmask; i++) MEMBER_D[i] = 0;
	for (j=0; j < (int)BSize; j++) {
		for(i=m-1; i >= j; i--) {
			hash = 0;
			for(k=0; k <= j; k++)
				hash = (hash << LOG_DNA) +char_map[Pattern[i-k]];
#ifdef DEBUG
			printf("< %d >, ", hash);
#endif
			MEMBER_D[hash] = 1;
		}
	}
}
