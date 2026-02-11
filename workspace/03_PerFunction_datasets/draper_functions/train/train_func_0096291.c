remoteop_chown(const char *path, uid_t uid, gid_t gid)
{
    int res;
    char *p;

    if (discofs_options.copyattr & COPYATTR_NO_OWNER)
        uid = -1;
    if (discofs_options.copyattr & COPYATTR_NO_GROUP)
        gid = -1;

    if (uid == -1 && gid == -1)
        return 0;

    p = remote_path(path);
    if (!p)
        return -EIO;

    res = chown(p, uid, gid);
    free(p);

    if (res)
        return -errno;

    return 0;
}
