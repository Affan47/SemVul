ps_memory (void *prev_addr, PSL_LONG nelem, size_t size)
{
	void *tmp;

	if (nelem == 0) return (VNULL);

	if (prev_addr) {
		if ((tmp = realloc ((void *) prev_addr, (size_t)(nelem * size))) == VNULL) {
			fprintf (stderr, "PSL Fatal Error: Could not reallocate more memory, n = %ld\n", nelem);
			PS_exit (EXIT_FAILURE);
		}
	}
	else {
		if ((tmp = calloc ((size_t) nelem, size)) == VNULL) {
			fprintf (stderr, "PSL Fatal Error: Could not allocate memory, n = %ld\n", nelem);
			PS_exit (EXIT_FAILURE);
		}
	}
	return (tmp);
}
