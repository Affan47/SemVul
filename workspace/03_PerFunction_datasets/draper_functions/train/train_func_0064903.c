cli_realloc(void *ptr, size_t size)
{
	void *alloc;


    if(!size || size > CLI_MAX_ALLOCATION) {
	cli_errmsg("cli_realloc(): Attempt to allocate %lu bytes. Please report to http://bugs.clamav.net\n", (unsigned long int) size);
	return NULL;
    }

    alloc = realloc(ptr, size);

    if(!alloc) {
	perror("realloc_problem");
	cli_errmsg("cli_realloc(): Can't re-allocate memory to %lu bytes.\n", (unsigned long int) size);
	return NULL;
    } else return alloc;
}
