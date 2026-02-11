convci(register int n, register char *s)
#endif
{
	ftnint sum, t;
	char buff[100], *s0;
	int n0;

	s0 = s;
	n0 = n;
	sum = 0;
	while(n-- > 0) {

		t = *s++ - '0';
		if (sum > LONG_MAX/10) {
 ovfl:
			if (n0 > 60)
				n0 = 60;
			sprintf(buff, "integer constant %.*s truncated.",
				n0, s0);
			err(buff);
			return LONG_MAX;
			}
		sum *= 10;
		if (sum > LONG_MAX - t)
			goto ovfl;
		sum += t;
		}
	return(sum);
	}
