find_word(void)
{
    char        *p, *q;
    char        *new;
    SIZE_T      len;

    p = &Line[Point];
    while (p > Line) {
        p--;
        if (p > Line && p[-1] == '\\') {
            p--;
        } else {
            if (strchr(SEPS, (char) *p) != NULL) {
                p++;
                break;
            }
        }
    }
    len = Point - (p - Line) + 1;
    if ((new = NEW(char, len)) == NULL)
        return NULL;
    q = new;
    while (p < &Line[Point]) {
        if (*p == '\\') {
            if (++p == &Line[Point]) break;
        }
        *q++ = *p++;
    }
    *q = '\0';
    return new;
}
