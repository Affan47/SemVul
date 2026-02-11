msg_compress_match_name(char **result, char *buf, char *name)
{
    int len;

    for (;;) {
        if (strcasecmp(buf, name) == 0) {
            *result = buf;
            return 1;
        }

        len = *buf;
        if (len == 0) {
            *result = buf + 1;
            break;
        } else if (len & 0xc0) {
            *result = buf + 2;
            break;
        } else
            buf += len + 1;
    }

    return 0;
}
