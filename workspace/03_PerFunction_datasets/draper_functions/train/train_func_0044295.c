sync_start_readtime(int fd, const char *path)
{
    syncmsg msg;
    int len = strlen(path);

    msg.req.id = ID_STAT;
    msg.req.namelen = htoll(len);

    if(writex(fd, &msg.req, sizeof(msg.req)) ||
       writex(fd, path, len)) {
        return -1;
    }

    return 0;
}
