number(long big)
{
	char *cs;
	vlong n;

	cs = string;
	n = 0;
	while(*cs >= '0' && *cs <= '9')
		n = n*10 + *cs++ - '0';
	for(;;)
	switch(*cs++) {

	case 'k':
		n *= 1024;
		continue;


	case 'b':
		n *= 512;
		continue;


	case 'x':
		string = cs;
		n *= number(BIG);

	case '\0':
		if(n>=big || n<0) {
			fprint(2, "dd: argument %lld out of range\n", n);
			exits("range");
		}
		return n;
	}

}
