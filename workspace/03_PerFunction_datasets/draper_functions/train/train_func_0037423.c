st_pread(int fd, void *buf, size_t nbyte, off_t off, struct storage_st *st)
{
char	localbuf[2*512], *start_b, *rounded_b;
char    *rounded_data;
ssize_t	res, rnbyte;

    if ( !IS_CHARDEV(st) ) {
	return(pread(fd,buf,nbyte,off));
    }
    if ( nbyte < 512 ) {
        start_b = &localbuf[0];
        rounded_b = (char*)(((uintptr_t)start_b/512)*512);
        if ( rounded_b < &localbuf[0] ) rounded_b += 512;
	res = pread(fd,rounded_b, 512, off);
	if ( res > 0 ) {
	    memcpy(buf, rounded_b, MIN(nbyte, res));
	    return(MIN(nbyte, res));
        }
	my_xlog(OOPS_LOG_SEVERE, "st_pread(%d, %d): %m\n", fd, nbyte);
	return(res);
    }
    rnbyte = (nbyte/512)*512;
    if ( rnbyte < nbyte ) rnbyte+=512;
#if	defined(SOLARIS)
    rounded_data = memalign(512, rnbyte);
#else
    rounded_data = malloc(ROUND_UP(PAGE_SIZE, rnbyte));
#endif
    if ( !rounded_data ) {
        return(-1);
    }
    res = pread(fd,rounded_data,rnbyte,off);
    if ( res <= 0 ) {
        free(rounded_data);
        return(res);
    }
    memcpy(buf, rounded_data, MIN(res,nbyte));
    free(rounded_data);
    return(MIN(res,nbyte));
}
