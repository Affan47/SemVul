doComputation(PTW2_attackstate * state, uint8_t * key, int keylen, PTW2_tableentry table[][n], sorthelper * sh2, int * strongbytes, int keylimit, int * bf, int validchars[][n]) {
	int i,j;
	int choices[KEYHSBYTES];
	int prod;
	int fixat;
	int fixvalue;

        if(!opt.is_quiet)
            memcpy(keytable, table, sizeof(PTW2_tableentry) * n * keylen);

	for (i = 0; i < keylen; i++) {
		if (strongbytes[i] == 1) {
			choices[i] = i;
		} else {
			choices[i] = 1;
		}
	}
	i = 0;
	prod = 0;
	fixat = -1;
	fixvalue = 0;
        max_tries = keylimit;

	while(prod < keylimit) {
		if (doRound(table, 0, fixat, fixvalue, choices, key, keylen, state, 0, strongbytes, bf, validchars) == 1) {

			return 1;
		}
		while( (i < (keylen-1) * (n-1)) && ((strongbytes[sh2[i].keybyte] == 1) || (bf[sh2[i].keybyte] == 1) ) ) {
			i++;
		}
		if(i >= ((keylen-1) * (n-1)))
		{
			break;
		}
		choices[sh2[i].keybyte]++;
		fixat = sh2[i].keybyte;

		fixvalue = sh2[i].value;
		prod = 1;
		for (j = 0; j < keylen; j++) {
			prod *= choices[j];
			if (bf[j] == 1) {
				prod *= n;
			}
		}


		i++;


	}
    return 0;
}
