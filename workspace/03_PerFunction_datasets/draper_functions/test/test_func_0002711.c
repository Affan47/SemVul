check_file(int fd) {
    int rc;
    char buf[1024];
    if (lseek(fd, 0, SEEK_SET) == (loff_t)(-1)) {
    	perror("lseek(file)");
    	exit(-1);
    }
    rc = read(fd, buf, sizeof(msg));
    if (rc != sizeof(msg)) {
    	perror("read(file)");
    	exit(-1);
    }
    if (strcmp(msg, buf)) {
    	fprintf(stderr, "Compare of file to original failed\n");
    	exit(-1);
    }
    close(fd);
}
