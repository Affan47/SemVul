replace(const char* src, const char* dest) const {
    if (empty() || src == NULL || dest == NULL)
        return *this;
    size_t len = strlen(src);
    if (len > fString->len())
        return *this;

    plString result;
    size_t begin = 0;
    size_t i = 0;
    while (i < (fString->len() - len)) {
        if (strncmp(fString->data() + i, src, len) == 0) {
            result += plString(fString->data() + begin, i - begin);
            result += dest;
            i += len;
            begin = i;
        } else {
            i++;
        }
    }
    return result + plString(fString->data() + begin, (i + 1) - begin);
}
