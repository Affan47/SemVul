shm_brk(void *newbrk)
{
char 	tmp = 0;
int	flags = MAP_SHARED|MAP_FIXED;

    if (mfd < 0) flags |= MAP_ANONYMOUS;
    if (newbrk <= membase->brk) {
	if (ftruncate(mfd, newbrk - (void *)membase) < 0)
	    return -1;
	if (newbrk < membase->eof)
	    munmap(newbrk, membase->eof - newbrk);
	membase->brk = membase->eof = localbrk = newbrk; }
    else if (newbrk <= membase->eof) {
	membase->brk = newbrk;
	if (newbrk > localbrk) {
	    if (mfd >= 0) lseek(mfd, 0, SEEK_SET);
	    if ((long)mmap(localbrk, membase->eof - localbrk,
			   PROT_READ|PROT_WRITE, flags, mfd,
			   localbrk - (void *)membase) == -1)
		return -1;
	    localbrk = membase->eof; } }
    else {
	void *neweof = membase->brk + PAGESIZE * MMAP_INCR;
	if (newbrk > neweof)
	    neweof = newbrk;
	if (mfd >= 0) {
	    if (ftruncate(mfd, neweof - (void *)membase) < 0)
		return -1;
	    if (lseek(mfd, neweof - (void *)membase - 1, SEEK_SET) < 0)
		return -1;
	    if (write(mfd, &tmp, 1) != 1)
		return -1;
	    lseek(mfd, 0, SEEK_SET); }
	membase->eof = neweof;
	if ((long)mmap(localbrk, neweof - localbrk,
		       PROT_READ|PROT_WRITE, flags, mfd,
		       localbrk - (void *)membase) == -1)
	    return -1;
	localbrk = neweof;
	membase->brk = newbrk; }
    return 0;
}
