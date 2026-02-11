_pls_find_n_entries_end(int fd, const struct lms_file_info *finfo, struct lms_playlist_info *info)
{
    char buf[PLS_MAX_N_ENTRIES_BYTES_LOOKUP];
    ssize_t r;
    int i, last_nl;

    if (finfo->size > sizeof(buf))
        if (lseek(fd, finfo->size - sizeof(buf), SEEK_SET) < 0) {
            perror("lseek");
            return -1;
        }

    r = read(fd, buf, sizeof(buf));
    if (r < 0) {
        perror("read");
        return -1;
    } else if (r == 0)
        return -2;

    last_nl = -1;
    for (i = r - 1; i >= 0; i--) {
        if (buf[i] == '\n') {
            if (last_nl >= 0) {
                int len;

                len = last_nl - i - 1;
                if (len > 0) {
                    int ret;

                    ret = _pls_parse_entries_line(fd, info, buf + i + 1, len);
                    if (ret <= 0)
                        return ret;
                }
            }
            last_nl = i;
        }
    }

    return 1;
}
