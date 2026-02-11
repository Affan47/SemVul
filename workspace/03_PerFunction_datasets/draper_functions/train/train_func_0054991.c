inet_aton ( const char *cp, struct in_addr *inp ) {
	const char *p = cp;
	const char *digits_start;
	unsigned long ip = 0;
	unsigned long val;
	int j;
	for(j = 0; j <= 3; j++) {
		digits_start = p;
		val = strtoul(p, ( char ** ) &p, 10);
		if ((p == digits_start) || (val > 255)) return 0;
		if ( ( j < 3 ) && ( *(p++) != '.' ) ) return 0;
		ip = (ip << 8) | val;
	}
	if ( *p == '\0' ) {
		inp->s_addr = htonl(ip);
		return 1;
	}
	return 0;
}
