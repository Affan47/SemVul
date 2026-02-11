check_pattern(int fd, int length)
{
    int retval = -1;
    int seed;
    char *buf;

    seed = lseek(fd, 0, SEEK_CUR);
    if (seed < 0) {
        perror("lseek");
        goto out;
    }

    buf = malloc(length);
    if (buf == NULL) {
        perror("malloc");
        goto out;
    }

    retval = read(fd, buf, length);
    if (retval < 0) {
        perror("read");
        goto out_free;
    }

    retval = pattern_compare(buf, length, seed);
    if (retval < 0) {
        CRUT_FAIL("File failed to match expected contents at recovery.");
    }

out_free:
    free(buf);
out:
    return retval;
}
