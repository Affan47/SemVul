alloc(lth)
register unsigned int lth;
{
#ifdef LINT


	long dummy = ftell(stderr);

	if(lth) dummy = 0;
	return(&dummy);
#else
	register genericptr_t ptr;

	ptr = malloc(lth);
#ifndef MONITOR_HEAP
	if (!ptr) panic("Memory allocation failure; cannot get %u bytes", lth);
#endif
	return((long *) ptr);
#endif
}
