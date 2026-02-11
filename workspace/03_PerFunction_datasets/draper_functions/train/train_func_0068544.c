prep_fifo(const char *name) {
    int fd;
    if (mknod(name, 0600 | S_IFIFO, 0)) {
    	perror("mknod(fifo)");
    	exit(-1);
    }
    fd = open(name, O_RDWR);
    if (fd < 0) {
    	perror("open(fifo)");
    	exit(-1);
    }
    return fd;
}
