monsndx(ptr)
	struct	permonst	*ptr;
{
	register int	i;

	i = (int)(ptr - &mons[0]);
	if (i < LOW_PM || i >= NUMMONS) {

	    panic("monsndx - could not index monster (%lx)",
		  (unsigned long)ptr);
	    return NON_PM;
	}

	return(i);
}
