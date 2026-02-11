qhashmd5_file(const char *filepath, off_t offset, ssize_t nbytes,
                   void *retbuf) {
    if (filepath == NULL || offset < 0 || nbytes < 0 || retbuf == NULL) {
        errno = EINVAL;
        return false;
    }

    int fd = open(filepath, O_RDONLY, 0);
    if (fd < 0)
        return false;

    struct stat st;
    if (fstat(fd, &st) < 0)
        return false;
    size_t size = st.st_size;


    if (size < offset + nbytes) {
        errno = EINVAL;
        close(fd);
        return false;
    }


    if (offset > 0) {
        if (lseek(fd, offset, SEEK_SET) != offset) {
            close(fd);
            return false;
        }
    }

    MD5_CTX context;
    MD5Init(&context);
    ssize_t toread, nread;
    unsigned char buf[32 * 1024];
    for (toread = nbytes; toread > 0; toread -= nread) {
        if (toread > sizeof(buf))
            nread = read(fd, buf, sizeof(buf));
        else
            nread = read(fd, buf, toread);
        if (nread < 0)
            break;
        MD5Update(&context, buf, nread);
    }
    close(fd);
    if (toread != 0)
        return false;
    MD5Final(retbuf, &context);

    return true;
}
