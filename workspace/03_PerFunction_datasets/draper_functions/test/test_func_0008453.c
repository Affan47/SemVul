is_changelog(char *filename)
{
    char *ptr = NULL;
    int dashes = 0;
    int underscore = 0;
    if (NULL == (ptr = strrchr(filename, '/'))) {
        if (NULL == (ptr = strrchr(filename, '\\'))) {
            ptr = filename;
        } else {
            ptr++;
        }
    } else {
        ptr++;
    }
    for (; ptr && *ptr; ptr++) {
        if ('.' == *ptr) {
            if (0 == strncmp(ptr, ".db", 3)) {
                if (3 == dashes && 1 == underscore) {
                    return 1;
                } else {
                    return 0;
                }
            }
        } else if ('-' == *ptr) {
            if (underscore > 0) {
                return 0;
            }
            dashes++;
        } else if ('_' == *ptr) {
            if (dashes < 3) {
                return 0;
            }
            underscore++;
        } else if (!isxdigit(*ptr)) {
            return 0;
        }
    }
    return 0;
}
