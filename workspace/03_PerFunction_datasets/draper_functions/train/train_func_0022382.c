safemalloc(MEM_SIZE size)
{
    Malloc_t ptr;


    ptr = malloc(size ? size : 1);
#ifdef DEBUGGING
    if (debug & 128)
	fprintf(stderr,"0x%lx: (%05d) malloc %ld bytes\n",(unsigned long)ptr,
    	    	an++,(long)size);
#endif
    if (ptr != NULL)
	return ptr;
    else {
	fputs(nomem,stdout) FLUSH;
	exit(1);
    }

    return 0;
}
