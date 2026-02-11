cstrcasecmp(const char *a, const char *b, size_t n)
{
    char cb;

    for (; n > 0; a++, b++, n--) {
        cb = *b;
        if (cb >= 'a' && cb <= 'z') {
            cb -= 0x20;
        }
        if (*a != cb) {
            return *a - cb;
        } else if (*a == '\0') {
            return -1;
        }
    }

    return (*a == 0) ? 0 : 1;
}
