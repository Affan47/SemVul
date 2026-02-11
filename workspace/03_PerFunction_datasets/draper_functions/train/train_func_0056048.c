mprAddNullToBuf(MprBuf *bp)
{
    ssize      space;

    space = bp->endbuf - bp->end;
    if (space < sizeof(char)) {
        if (mprGrowBuf(bp, 1) < 0) {
            return;
        }
    }
    mprAssert(bp->end < bp->endbuf);
    if (bp->end < bp->endbuf) {
        *((char*) bp->end) = (char) '\0';
    }
}
