walscandir(Wal *w)
{
    static char base[] = "binlog.";
    static const int len = sizeof(base) - 1;
    DIR *d;
    struct dirent *e;
    int min = 1<<30;
    int max = 0;
    int n;
    char *p;

    d = opendir(w->dir);
    if (!d) return min;

    while ((e = readdir(d))) {
        if (strncmp(e->d_name, base, len) == 0) {
            n = strtol(e->d_name+len, &p, 10);
            if (p && *p == '\0') {
                if (n > max) max = n;
                if (n < min) min = n;
            }
        }
    }

    closedir(d);
    w->next = max + 1;
    return min;
}
