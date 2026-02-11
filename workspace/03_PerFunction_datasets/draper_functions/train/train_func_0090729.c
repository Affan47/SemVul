ckalloc(register int n)
#endif
{
	register ptr p;
	p = (ptr)calloc(1, (unsigned) n);
	if (p || !n)
		return(p);
	fprintf(stderr, "failing to get %d bytes\n",n);
	Fatal("out of memory");
	 return 0;
}
