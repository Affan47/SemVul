_read_string(int fd, char **out, unsigned int *out_len)
{
    char *s;
    uint16_t len;

    if (read(fd, &len, 2) == -1)
        return -1;

    len = be16toh(len);

    if (out) {
        if (len > 0) {
            s = malloc(sizeof(char) * (len + 1));
            if (read(fd, s, len) == -1) {
                free(s);
                return -1;
            }
            s[len] = '\0';
            *out = s;
        } else
            *out = NULL;

        *out_len = len;
    } else
        lseek(fd, len, SEEK_CUR);

    return 0;
}
