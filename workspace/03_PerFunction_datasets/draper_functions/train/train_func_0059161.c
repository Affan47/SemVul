putfile(void)
{
	int *a1;
	Rune *lp;
	long c;

	a1 = addr1;
	do {
		lp = getline(*a1++);
		for(;;) {
			count++;
			c = *lp++;
			if(c == 0) {
				if(Bputrune(&iobuf, '\n') < 0)
					error(Q);
				break;
			}
			if(Bputrune(&iobuf, c) < 0)
				error(Q);
		}
	} while(a1 <= addr2);
	if(Bflush(&iobuf) < 0)
		error(Q);
}
