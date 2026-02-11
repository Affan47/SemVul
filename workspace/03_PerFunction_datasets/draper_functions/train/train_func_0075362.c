xmlSchemaNormLen(const xmlChar *value) {
    const xmlChar *utf;
    int ret = 0;

    if (value == NULL)
        return(-1);
    utf = value;
    while (IS_BLANK_CH(*utf)) utf++;
    while (*utf != 0) {
        if (utf[0] & 0x80) {
            if ((utf[1] & 0xc0) != 0x80)
                return(-1);
            if ((utf[0] & 0xe0) == 0xe0) {
                if ((utf[2] & 0xc0) != 0x80)
                    return(-1);
                if ((utf[0] & 0xf0) == 0xf0) {
                    if ((utf[0] & 0xf8) != 0xf0 || (utf[3] & 0xc0) != 0x80)
                        return(-1);
                    utf += 4;
                } else {
                    utf += 3;
                }
            } else {
                utf += 2;
            }
        } else if (IS_BLANK_CH(*utf)) {
            while (IS_BLANK_CH(*utf)) utf++;
            if (*utf == 0)
                break;
        } else {
            utf++;
        }
        ret++;
    }
    return(ret);
}
