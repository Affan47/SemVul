ParseCryptoPAnKey ( char *s, char *key ) {
int i, j;
char numstr[3];
uint32_t len = strlen(s);

	if ( len < 32  || len > 66 ) {
		fprintf(stderr, "*** CryptoPAnKey error: size: %u\n", len);
		fprintf(stderr, "*** Need either a plain 32 char string, or a 32 byte hex key starting with 0x..\n");
		return 0;
	}

	if ( strlen(s) == 32 ) {

		strncpy(key, s, 32);
		return 1;
	}

	s[1] = tolower(s[1]);
	numstr[2] = 0;
	if ( strlen(s) == 66 && s[0] == '0' && s[1] == 'x' ) {
		j = 2;
		for ( i=0; i<32; i++ ) {
			if ( !isxdigit((int)s[j]) || !isxdigit((int)s[j+1]) )
				return 0;
			numstr[0] = s[j++];
			numstr[1] = s[j++];
			key[i] = strtol(numstr, NULL, 16);
		}
		return 1;
	}


	fprintf(stderr, "*** CryptoPAnKey error: size: %u\n", len);
	fprintf(stderr, "*** Need either a plain 32 char string, or a 32 byte hex key starting with 0x..\n");
	return 0;

}
