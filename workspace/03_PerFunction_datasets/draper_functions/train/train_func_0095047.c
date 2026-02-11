copyn(register int n, register char *s)
#endif
{
	register char *p, *q;

	p = q = (char *) Alloc(n);
	while(--n >= 0)
		*q++ = *s++;
	return(p);
}
