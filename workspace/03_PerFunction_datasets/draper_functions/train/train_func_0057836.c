standard_utime(archive_file_ty *afp, struct utimbuf *ut)
{
    struct ar_hdr   *h;
    int             nbytes;

    h = afp->header;
    assert(h);
    numset(h->ar_date, sizeof(h->ar_date), ut->modtime);
    assert(number(h->ar_date, sizeof(h->ar_date)) == ut->modtime);
    nbytes = write(afp->fd, h, sizeof(*h));
    if (nbytes < 0)
        return -1;
    if (nbytes != sizeof(*h))
    {
        errno = EIO;
        return -1;
    }
    return 0;
}
