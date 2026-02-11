valloc(size_t size)
{
void			*new;

    size = (size + PAGESIZE - 1)/PAGESIZE;
    if (!membase) minit();
    LOCK(NUMSMALL);
    if (!(new = alloc_pages(size))) {
	if ((new = sbrk(size * PAGESIZE)) == (void *)-1) {
	    UNLOCK(NUMSMALL);
	    return 0; }
	if ((U)new % PAGESIZE) {
	    if (sbrk(PAGESIZE - (U)new % PAGESIZE) == (void *)-1) {
		if (brk(new)) ;
		UNLOCK(NUMSMALL);
		return 0; }
	    new += PAGESIZE - (U)new % PAGESIZE; }
	if (I1(PAGENUM(new)+size-1) != I1(PAGENUM(membase->end)-1)) {
	    if (!expand_page_table(PAGENUM(new)+size-1)) {
		if ((U)new > (U)membase->end) {
		    if (brk(new)) ;
		    UNLOCK(NUMSMALL);
		    return 0; } }
	} else
	    membase->end = new + size*PAGESIZE;
	setup_extent_descriptor(new, size); }
    UNLOCK(NUMSMALL);
    return new;
}
