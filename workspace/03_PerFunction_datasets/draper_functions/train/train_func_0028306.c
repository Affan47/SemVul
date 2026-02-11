putcore(hash_table *tab)
{
    size_t size;
    ssize_t result;

    if (tab->incore == INCORE_MEM) {
	if(options.writethrough)
	    return true;
	nonblocking(tab->fd, false);
	size = tab->reclen * conf.tsize;
        result = xpwrite(tab->fd, tab->core, size, 0);
	if (result < 0 || (size_t) result != size) {
	    nonblocking(tab->fd, options.nonblock);
	    return false;
	}
	nonblocking(tab->fd, options.nonblock);
    }
#ifdef HAVE_MMAP
    if(tab->incore == INCORE_MMAP) {
	msync(tab->core, conf.tsize * tab->reclen, MS_ASYNC);
    }
#endif
    return true;
}
