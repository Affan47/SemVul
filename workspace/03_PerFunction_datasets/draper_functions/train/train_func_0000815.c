ios_fd(ios_t *s, long fd, int isfile, int own)
{
    _ios_init(s);
    s->fd = fd;
    if (isfile) s->rereadable = 1;
    _buf_init(s, bm_block);
    s->ownfd = own;
    if (fd == STDERR_FILENO)
        s->bm = bm_none;
    return s;
}
