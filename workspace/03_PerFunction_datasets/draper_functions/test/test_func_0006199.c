create_textfile(const char *name, size_t size)
{
    char *buf;
    int fd;
    size_t i;
    char *bp;

    fd = HDcreat(name,0777);
    HDassert(fd >= 0);
    buf = HDcalloc(size, (size_t)1);
    HDassert(buf);


    bp = buf;
    for(i = 0; i < size; i++)
        *bp++ = pattern[i % 10];

    HDwrite(fd, buf, size);

    HDfree(buf);

    HDclose(fd);
}
