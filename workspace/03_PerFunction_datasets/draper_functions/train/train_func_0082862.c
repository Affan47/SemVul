int32_decode(cram_fd *fd, int32_t *val) {
    int32_t i;
    if (4 != hread(fd->fp, &i, 4))
	return -1;

    *val = le_int4(i);
    return 4;
}
