av_file_open(vfile *vf, ventry *ve, int flags, avmode_t mode)
{
    int res;
    struct avfs *avfs = ve->mnt->avfs;

    res = av_copy_vmount(ve->mnt, &vf->mnt);
    if(res < 0)
	return res;

    if((flags & AVO_EXCL) != 0 && (flags & AVO_CREAT) == 0)
        flags &= ~AVO_EXCL;

    if((flags & AVO_TRUNC) != 0 && !AV_ISWRITE(flags)) {
        if((flags & AVO_ACCMODE) == AVO_RDONLY)
            flags = (flags & ~AVO_ACCMODE) | AVO_RDWR;
        else
            flags = (flags & ~AVO_ACCMODE) | AVO_WRONLY;
    }

    AVFS_LOCK(avfs);
    res = avfs->open(ve, flags, (mode & 07777), &vf->data);
    AVFS_UNLOCK(avfs);
    if(res < 0) {
	av_free_vmount(vf->mnt);
        vf->mnt = NULL;
        return res;
    }

    vf->ptr = 0;
    vf->flags = flags;

    return 0;
}
