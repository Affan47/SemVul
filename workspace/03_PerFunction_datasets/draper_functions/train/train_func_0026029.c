removc(Blk *p, int n)
{
	Blk *q, *r;

	rewind(p);
	while(n>1) {
		skipc(p);
		n -= 2;
	}
	q = salloc(2);
	while(sfeof(p) == 0)
		sputc(q,sgetc(p));
	if(n == 1) {
		r = div(q,tenptr);
		release(q);
		release(rem);
		q = r;
	}
	release(p);
	return(q);
}
