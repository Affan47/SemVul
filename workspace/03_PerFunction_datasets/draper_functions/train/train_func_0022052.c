mulby(char *a, char *p, char *q, int b)
{
	int n, c;

	n = 0;
	*p = 0;
	for(;;) {
		q--;
		if(q < a)
			break;
		c = *q - '0';
		c = (c<<b) + n;
		n = c/10;
		c -= n*10;
		p--;
		*p = c + '0';
	}
	while(n) {
		c = n;
		n = c/10;
		c -= n*10;
		p--;
		*p = c + '0';
	}
}
