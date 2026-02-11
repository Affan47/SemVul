_jpeg_data_get(int fd, int *type, int *len)
{
    unsigned char buf[6];

    if (lseek(fd, 0, SEEK_SET) != 0) {
        perror("lseek");
        return -1;
    }

    if (read(fd, buf, 6) != 6) {
        perror("read");
        return -2;
    }

    if (buf[0] != 0xff || buf[1] != JPEG_MARKER_SOI || buf[2] != 0xff) {
        fprintf(stderr, "ERROR: not JPEG file (magic=%#x %#x %#x)\n",
                buf[0], buf[1], buf[2]);
        return -3;
    }

    *type = buf[3];
    *len = (buf[4] << 8) | buf[5];

    return 0;
}
