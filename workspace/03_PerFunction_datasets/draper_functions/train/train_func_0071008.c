wire_findbody(const char *article, size_t length)
{
    char *p;
    const char *end;


    if (length > 5 && article[0] == '\r' && article[1] == '\n')
        return (char *) article + 2;


    end = article + length;
    for (p = (char *) article; (p + 4) <= end; ++p) {
        p = memchr(p, '\r', end - p - 3);
        if (p == NULL)
            break;
        if (memcmp(p, "\r\n\r\n", 4) == 0) {
            p += 4;
            return p;
        }
    }
    return NULL;
}
