myfr(FILE *fd, void *data, unsigned size) {
    int     len;

    len = fread(data, 1, size, fd);
    if(len == size) return;
    if(!multi) {
        printf("\nError: incomplete input file, can't read %u bytes\n", size);
        myexit(NULL);
    }
    fclose(fd);
    fd = daa_next();
    myfr(fd, data + len, size - len);
}
