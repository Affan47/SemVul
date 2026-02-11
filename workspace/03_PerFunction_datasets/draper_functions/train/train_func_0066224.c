sfile_writeout(struct sfile *fil, void *conndata)
{
    avssize_t res;
    const int tmpbufsize = 8192;
    char tmpbuf[tmpbufsize];
    avoff_t offset;

    for(offset = 0; offset < fil->numbytes;) {
        avsize_t nact = AV_MIN(tmpbufsize, fil->numbytes - offset);

        res = sfile_cached_pread(fil, tmpbuf, nact, offset);
        if(res < 0)
            return res;

        res = fil->func->write(conndata, tmpbuf, nact);
        if(res < 0)
            return res;

        offset += res;
    }

    return 0;
}
