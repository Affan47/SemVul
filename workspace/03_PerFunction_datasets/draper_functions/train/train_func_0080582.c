wire_nextline(const char *article, const char *end)
{
    char *p;

    for (p = (char *) article; (p + 2) <= end; ++p) {
        p = memchr(p, '\r', end - p - 2);
        if (p == NULL)
            break;
        if (p[1] == '\n') {
            p += 2;
            return p;
        }
    }
    return NULL;
}
