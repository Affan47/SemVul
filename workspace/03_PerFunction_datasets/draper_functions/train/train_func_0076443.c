ParseSearchOptions(int replace, const char *str, unsigned long &Options) {
    const char *p = str;

    Options = SEARCH_NEXT;
    while (*p) {
        if (ParseSearchOption(replace, *p, Options) == 0) return 0;
        p++;
    }
    return 1;
}
