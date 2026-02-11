browse(void)
{
	int forward, n;
	static int bformat, bnum;

	forward = 1;
	peekc = getchr();
	if(peekc != '\n'){
		if(peekc == '-' || peekc == '+') {
			if(peekc == '-')
				forward = 0;
			getchr();
		}
		n = getnum();
		if(n > 0)
			bpagesize = n;
	}
	newline();
	if(pflag) {
		bformat = listf;
		bnum = listn;
	} else {
		listf = bformat;
		listn = bnum;
	}
	if(forward) {
		addr1 = addr2;
		addr2 += bpagesize;
		if(addr2 > dol)
			addr2 = dol;
	} else {
		addr1 = addr2-bpagesize;
		if(addr1 <= zero)
			addr1 = zero+1;
	}
	printcom();
}
