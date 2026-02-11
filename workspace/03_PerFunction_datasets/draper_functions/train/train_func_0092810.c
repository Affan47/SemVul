lms_charset_conv_check(lms_charset_conv_t *lcc, const char *str, unsigned int len)
{
    char *outstr;
    int r, outlen;

    if (!lcc)
        return -1;
    if (!str || !len)
        return 0;

    outlen = 2 * len;
    outstr = malloc(outlen);
    if (!outstr) {
        perror("malloc");
        return -2;
    }

    r = _check(lcc, str, len, outstr, outlen);
    free(outstr);
    return r;
}
