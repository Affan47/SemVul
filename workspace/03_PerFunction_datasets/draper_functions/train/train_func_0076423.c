TabularHline(const char *row)


{
    char *s, *t;

    if (row == NULL)
        return 0;

    s = strstr(row, "\\hline");
    if (s == NULL)
        return 0;

    t = strstr(s + 6, "\\hline");

    if (t == NULL)
        return 1;
    return 2;
}
