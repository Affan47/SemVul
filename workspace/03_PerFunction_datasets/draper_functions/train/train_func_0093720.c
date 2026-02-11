strlen3(s)
CONST char *s;
{
	int r, v, rw, vw;

	r = v = 0;
	while (s[r]) {
		getcharwidth(s, r, &rw, &vw);
		r += rw;
		v += vw;
	}

	return(v);
}
