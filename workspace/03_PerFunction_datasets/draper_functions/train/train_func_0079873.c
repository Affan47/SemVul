utf8len(const pl_wchar_t* str, size_t srclen) {
    if (str == NULL)
        return 0;

    size_t len = 0;
    const pl_wchar_t* end = str + srclen;
    while (str < end) {
        if (*str < 0x80) {
            len += 1;
        } else if (*str < 0x800) {
            len += 2;
        } else {
            len += 3;
        }
        str++;
    }
    return len;
}
