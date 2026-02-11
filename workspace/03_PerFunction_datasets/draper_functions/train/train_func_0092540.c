count_temporary_files(void) {
    static int num;
    static time_t last_counted;
    if (last_counted < time(NULL) - 5) {
        DIR *d;
        struct dirent *de;
        num = 0;
        d = opendir(tmpdir);
        if (d) {
            while ((de = readdir(d))) {
                char *p;
                p = strrchr(de->d_name, '.');
                if (p && (strncmp(de->d_name, "driftnet-", 9) == 0 && (strcmp(p, ".jpeg") == 0 || strcmp(p, ".gif") == 0 || strcmp(p, ".mp3") == 0)))
                    ++num;
            }
            closedir(d);
            last_counted = time(NULL);
        }
    }
    return num;
}
