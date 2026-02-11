open_path(vfile *vf, const char *path, int flags, avmode_t mode)
{
    int res;
    ventry *ve;

    res = av_get_ventry(path, !(flags & AVO_NOFOLLOW), &ve);
    if(res < 0)
        return res;

    res = av_file_open(vf, ve, flags, mode);
    av_free_ventry(ve);

    return res;
}
