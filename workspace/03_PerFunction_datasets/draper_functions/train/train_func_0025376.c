adb_download_buffer(const char *service, const void* data, int sz,
                        unsigned progress)
{
    char buf[4096];
    unsigned total;
    int fd;
    const unsigned char *ptr;

    sprintf(buf,"%s:%d", service, sz);
    fd = adb_connect(buf);
    if(fd < 0) {
        fprintf(stderr,"error: %s\n", adb_error());
        return -1;
    }

    int opt = CHUNK_SIZE;
    opt = setsockopt(fd, SOL_SOCKET, SO_SNDBUF, &opt, sizeof(opt));

    total = sz;
    ptr = data;

    if(progress) {
        char *x = strrchr(service, ':');
        if(x) service = x + 1;
    }

    while(sz > 0) {
        unsigned xfer = (sz > CHUNK_SIZE) ? CHUNK_SIZE : sz;
        if(writex(fd, ptr, xfer)) {
            adb_status(fd);
            fprintf(stderr,"* failed to write data '%s' *\n", adb_error());
            return -1;
        }
        sz -= xfer;
        ptr += xfer;
        if(progress) {
            printf("sending: '%s' %4d%%    \r", service, (int)(100LL - ((100LL * sz) / (total))));
            fflush(stdout);
        }
    }
    if(progress) {
        printf("\n");
    }

    if(readx(fd, buf, 4)){
        fprintf(stderr,"* error reading response *\n");
        adb_close(fd);
        return -1;
    }
    if(memcmp(buf, "OKAY", 4)) {
        buf[4] = 0;
        fprintf(stderr,"* error response '%s' *\n", buf);
        adb_close(fd);
        return -1;
    }

    adb_close(fd);
    return 0;
}
