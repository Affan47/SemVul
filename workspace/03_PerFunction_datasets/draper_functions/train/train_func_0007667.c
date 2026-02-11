av_unlink(ventry *ve)
{
    int res;
    struct avfs *avfs = ve->mnt->avfs;

    AVFS_LOCK(avfs);
    res = avfs->unlink(ve);
    AVFS_UNLOCK(avfs);

    return res;
}
