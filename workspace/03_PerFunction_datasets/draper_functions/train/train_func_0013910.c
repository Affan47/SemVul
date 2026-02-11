raw_getlength(BlockDriverState *bs)
{
    BDRVRawState *s = bs->opaque;
    int fd = s->fd;
    int64_t size;
#ifdef _BSD
    struct stat sb;
#endif
#ifdef __sun__
    struct dk_minfo minfo;
    int rv;
#endif
    int ret;

    ret = fd_open(bs);
    if (ret < 0)
        return ret;

#ifdef _BSD
    if (!fstat(fd, &sb) && (S_IFCHR & sb.st_mode)) {
#ifdef DIOCGMEDIASIZE
	if (ioctl(fd, DIOCGMEDIASIZE, (off_t *)&size))
#endif
#ifdef CONFIG_COCOA
        size = LONG_LONG_MAX;
#else
        size = lseek(fd, 0LL, SEEK_END);
#endif
    } else
#endif
#ifdef __sun__


    rv = ioctl ( fd, DKIOCGMEDIAINFO, &minfo );
    if ( rv != -1 ) {
        size = minfo.dki_lbsize * minfo.dki_capacity;
    } else


#endif
    {
        size = lseek(fd, 0, SEEK_END);
    }
    return size;
}
