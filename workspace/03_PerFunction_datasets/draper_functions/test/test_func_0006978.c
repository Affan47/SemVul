validBlk(MprMem *mp)
{
    ssize   size;

    size = GET_SIZE(mp);
    mprAssert(mp->magic == MPR_ALLOC_MAGIC);
    mprAssert(size > 0);
    return (mp->magic == MPR_ALLOC_MAGIC) && (size > 0);
}
