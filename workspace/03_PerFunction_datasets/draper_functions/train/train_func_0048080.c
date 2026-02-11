cache_fgetattr(const char *path, struct stat *stbuf,
                          struct fuse_file_info *fi)
{
    int err = cache_get_attr(path, stbuf);
    if (err == -EAGAIN) {
        err = cache.next_oper->oper.fgetattr(path, stbuf, fi);
        if (!err)
            cache_add_attr(path, stbuf);
        else if (err == -ENOENT)
            cache_add_attr(path, NULL);
    }
    return err;
}
