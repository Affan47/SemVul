vlen(s, cx)
CONST char *s;
int cx;
{
	int v, r, rw, vw;

	v = r = 0;
	while (r < cx) {
		getcharwidth(s, r, &rw, &vw);
		if (r + rw > cx) break;
		r += rw;
		v += vw;
	}

	return(v);
}
