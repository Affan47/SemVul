get_termcap_string(char const* id, char* dest, size_t n)
{
    char    tc[16];
    char   *tp = tc;
    tp[0] = '\0';
    tp = tgetstr(id, &tp);
    if (tp != NULL && dest != NULL && n > 0) {
        strncpy(dest, tp, n);
        dest[n-1] = '\0';
    }
}
