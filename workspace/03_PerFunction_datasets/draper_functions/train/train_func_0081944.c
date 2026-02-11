create_shmem_mmap(const char *path, size_t size, void** pp) {
    int fd, retval;
    struct stat sbuf;


    *pp = 0;
    if (size == 0) return ERR_SHMGET;


    fd = open(path, O_RDWR | O_CREAT, 0666);
    if (fd < 0) return ERR_SHMGET;

    retval = fstat(fd, &sbuf);
    if (retval) {
        close(fd);
        return ERR_SHMGET;
    }
    if (sbuf.st_size < (long)size) {


        lseek(fd, size-1, SEEK_SET);
        if (1 != write(fd, "\0", 1)) {
	    close(fd);
	    return ERR_SHMGET;
	}
    }

    *pp = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_FILE | MAP_SHARED, fd, 0);

    close(fd);

    if (*pp == MAP_FAILED) {
        *pp = 0;
        return ERR_SHMGET;
    }

    return 0;
}
