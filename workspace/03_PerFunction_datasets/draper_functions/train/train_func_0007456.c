CHANreadtext(CHANNEL *cp)
{
    struct buffer *bp;
    char *name;
    int oerrno, maxbyte;
    ssize_t count;


    bp = &cp->In;
    bp->left = bp->size - bp->used;
    if (bp->left <= LOW_WATER)
        CHANresize(cp, bp->size + GROW_AMOUNT(bp->size));


    if (innconf->maxcmdreadsize == 0 || cp->State != CSgetcmd
        || bp->left < innconf->maxcmdreadsize)
        maxbyte = bp->left;
    else
        maxbyte = innconf->maxcmdreadsize;
    TMRstart(TMR_NNTPREAD);
    count = read(cp->fd, &bp->data[bp->used], maxbyte);
    TMRstop(TMR_NNTPREAD);


    if (count < 0) {
        if (errno == EAGAIN)
            return -2;
        oerrno = errno;
        name = CHANname(cp);
        errno = oerrno;
        sysnotice("%s cant read", name);
        return -1;
    }
    if (count == 0) {
        name = CHANname(cp);
        notice("%s readclose", name);
        return 0;
    }
    bp->used += count;
    bp->left -= count;
    return count;
}
