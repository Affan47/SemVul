allocate(int size)
{
    void *addr;

    if (mem.last-mem.first+size > PAGE_SIZE) {
	if (size > PAGE_SIZE) runtime_error(_("memory allocation error"));
	if (*mem.cur == NULL) {
	    mem.first = malloc(PAGE_SIZE);
	    check_ptr(mem.first);
	    *mem.cur = mem.first;
	    mem.cur = (void **)mem.first;
	    *mem.cur = NULL;
	} else mem.first = *mem.cur;
	mem.last = mem.first + sizeof(void *);
    }
    addr = mem.last;
    mem.last += size;
    return addr;
}
