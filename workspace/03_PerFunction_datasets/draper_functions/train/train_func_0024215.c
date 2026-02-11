child_comm_send_filepath(int fd, const char *name, const char *path) {
    size_t namelen = strlen(name);
    size_t pathlen = strlen(path);
    void *buf;
    struct child_comm c;
    c.id   = CHILD_COMM_ID_FILEPATH;
    c.len  = namelen + 1 + pathlen + 1;
    c.data = buf = malloc(c.len);
    if (buf == NULL)
        return -1;

    memcpy(buf, name, namelen);
    buf += namelen;
    *((char *) buf++) = '\0';

    memcpy(buf, path, pathlen);
    buf += pathlen;
    *((char *) buf++) = '\0';

    int r = 0;
    if (child_comm_write(fd, &c) < 0)
        r = -1;
    free((void *) c.data);
    return r;
}
