readregion(pid_t target, void *buf, size_t count, unsigned long offset)
{
    char mem[32];
    int fd;
    ssize_t len;


    snprintf(mem, sizeof(mem), "/proc/%d/mem", target);


    if ((fd = open(mem, O_RDONLY)) == -1) {
        show_error("unable to open %s.\n", mem);
        return -1;
    }


    len = pread(fd, buf, count, offset);


    close(fd);

    return len;
}
