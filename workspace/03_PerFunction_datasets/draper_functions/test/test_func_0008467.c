__ziplistCascadeUpdate(unsigned char *zl, unsigned char *p) {
    size_t curlen = ZIPLIST_BYTES(zl), rawlen, rawlensize;
    size_t offset, noffset, extra;
    unsigned char *np;
    zlentry cur, next;

    while (p[0] != ZIP_END) {
        cur = zipEntry(p);
        rawlen = cur.headersize + cur.len;
        rawlensize = zipPrevEncodeLength(NULL,rawlen);


        if (p[rawlen] == ZIP_END) break;
        next = zipEntry(p+rawlen);


        if (next.prevrawlen == rawlen) break;

        if (next.prevrawlensize < rawlensize) {


            offset = p-zl;
            extra = rawlensize-next.prevrawlensize;
            zl = ziplistResize(zl,curlen+extra);
            p = zl+offset;


            np = p+rawlen;
            noffset = np-zl;


            if ((zl+ZIPLIST_TAIL_OFFSET(zl)) != np)
                ZIPLIST_TAIL_OFFSET(zl) += extra;


            memmove(np+rawlensize,
                np+next.prevrawlensize,
                curlen-noffset-next.prevrawlensize-1);
            zipPrevEncodeLength(np,rawlen);


            p += rawlen;
            curlen += extra;
        } else {
            if (next.prevrawlensize > rawlensize) {


                zipPrevEncodeLengthForceLarge(p+rawlen,rawlen);
            } else {
                zipPrevEncodeLength(p+rawlen,rawlen);
            }


            break;
        }
    }
    return zl;
}
