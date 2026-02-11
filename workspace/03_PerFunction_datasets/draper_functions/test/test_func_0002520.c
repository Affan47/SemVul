sfile_pread_start(struct sfile *fil, char *buf,
                                   avsize_t nbyte, avoff_t offset)
{
    int res;

    if((fil->flags & SFILE_NOCACHE) != 0 && offset < fil->numbytes)
        sfile_reset_usecache(fil);

    if(fil->state == SF_BEGIN) {
        res = sfile_startget(fil);
        if(res < 0)
            return res;
    }

    return sfile_pread(fil, buf, nbyte, offset);
}
