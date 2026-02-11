ucs2len(const char* str, size_t srclen) {
    if (str == NULL)
        return 0;

    size_t len = 0;
    const char* end = str + srclen;
    while (str < end) {
        if ((*str & 0x80) == 0) {
            str += 1;
        } else if ((*str & 0xE0) == 0xC0) {
            if ((*(str+1) & 0xC0) != 0x80)
                throw hsBadParamException(__FILE__, __LINE__, "Invalid UTF-8 sequence");
            str += 2;
        } else if ((*str & 0xF0) == 0xE0) {
            if ((*(str+1) & 0xC0) != 0x80 || (*(str+2) & 0xC0) != 0x80)
                throw hsBadParamException(__FILE__, __LINE__, "Invalid UTF-8 sequence");
            str += 3;
        } else if ((*str & 0xF1) == 0xF0) {
            throw hsBadParamException(__FILE__, __LINE__, "Unicode character out of UCS-2 range");
        } else {
            throw hsBadParamException(__FILE__, __LINE__, "Invalid UTF-8 sequence");
        }
        len++;
    }
    return len;
}
