readFile(char *filename){
    int fd;
    char *data;
    struct stat sbuf;

    if (filename == NULL) {
        fprintf(stderr, "Insert filename!\n");
        exit(1);
    }

    if ((fd = open(filename, O_RDONLY)) == -1) {
        perror("Error on opening file");
        exit(1);
    }

    if (stat(filename, &sbuf) == -1) {
        perror("Error on receiving stat");
        exit(1);
    }

    if ((data = mmap((caddr_t)0, sbuf.st_size, PROT_READ, MAP_SHARED, fd, 0)) == (caddr_t)(-1)) {
        perror("Could not map file");
        exit(1);
    }

    if (close(fd) == -1){
        perror("Error on closing file");
        exit(1);
    }
    return data;
}
