filewopen(File *f)
{
    int fd, r;
    int n;
    int ver = Walver;

    fd = open(f->path, O_WRONLY|O_CREAT, 0400);
    if (fd < 0) {
        twarn("open %s", f->path);
        return;
    }

    r = falloc(fd, f->w->filesz);
    if (r) {
        close(fd);
        errno = r;
        twarn("Cannot allocate space for file %s", f->path);
        return;
    }

    n = write(fd, &ver, sizeof(int));
    if (n < sizeof(int)) {
        twarn("write %s", f->path);
        close(fd);
        return;
    }

    f->fd = fd;
    f->iswopen = 1;
    fileincref(f);
    f->free = f->w->filesz - n;
    f->resv = 0;
}
