bz_same(struct bznode *nod, struct avstat *stbuf)
{
    if(nod->sig.ino == stbuf->ino &&
       nod->sig.dev == stbuf->dev &&
       nod->sig.size == stbuf->size &&
       AV_TIME_EQ(nod->sig.mtime, stbuf->mtime))
        return 1;
    else
        return 0;
}
