pr_ZoneRealloc(void *oldptr, PRUint32 bytes)
{
    void         *rv;
    MemBlockHdr  *mb;
    int           ours;
    MemBlockHdr   phony;

    if (!oldptr)
        return pr_ZoneMalloc(bytes);
    mb = (MemBlockHdr *)((char *)oldptr - (sizeof *mb));
    if (mb->s.magic != ZONE_MAGIC) {

#ifdef DEBUG
        fprintf(stderr,
            "Warning: reallocing memory block %p from ordinary malloc\n",
            oldptr);
#endif


        rv = pr_ZoneMalloc(bytes);
        if (!rv) {
            return rv;
        }


        oldptr = realloc(oldptr, bytes);


        if (!oldptr) {
            if (bytes) {
                PR_SetError(PR_OUT_OF_MEMORY_ERROR, 0);
                pr_ZoneFree(rv);
                return oldptr;
            }
        }
        phony.s.requestedSize = bytes;
        mb = &phony;
        ours = 0;
    } else {
        size_t blockSize = mb->s.blockSize;
        MemBlockHdr *mt = (MemBlockHdr *)(((char *)(mb + 1)) + blockSize);

        PR_ASSERT(mt->s.magic == ZONE_MAGIC);
        PR_ASSERT(mt->s.zone  == mb->s.zone);
        PR_ASSERT(mt->s.blockSize == blockSize);

        if (bytes <= blockSize) {

            mt->s.requestedSize = mb->s.requestedSize = bytes;
            return oldptr;
        }
        ours = 1;
        rv = pr_ZoneMalloc(bytes);
        if (!rv) {
            return rv;
        }
    }

    if (oldptr && mb->s.requestedSize)
        memcpy(rv, oldptr, mb->s.requestedSize);
    if (ours)
        pr_ZoneFree(oldptr);
    else if (oldptr)
        free(oldptr);
    return rv;
}
