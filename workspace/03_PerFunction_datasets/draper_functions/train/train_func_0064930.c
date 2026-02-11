biowrite(biop, ptr, nbytes)
biobuf *biop;
unsigned char *ptr;
int nbytes;
{
    size_t rem ;
    int nwrote = 0 ;
    int cnt ;

    if(!((biop->mode & O_WRONLY) || (biop->mode & O_RDWR)))
        return -1 ;

    while(nbytes > (rem = BREM(biop)))
    {
        if(rem > 0)
        {
            (void) memcpy(biop->ptr, ptr, rem) ;
            biop->isdirty = !0 ;
            biop->cnt = BIOBUFSIZ ;
            ptr += rem ;
            nbytes -= rem ;
            nwrote += rem ;
        }
        if(nextbuf(biop) < 0)
            return nwrote ;
    }

    (void) memcpy(biop->ptr, ptr, (size_t)nbytes) ;
    biop->isdirty = !0 ;
    biop->ptr += nbytes ;
    if((cnt = CNT(biop)) > biop->cnt)
        biop->cnt = cnt ;
    nwrote += nbytes ;

    return nwrote ;
}
