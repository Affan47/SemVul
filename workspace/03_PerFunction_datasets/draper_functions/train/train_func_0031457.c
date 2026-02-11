sync_sieve_delete(const char *userid, const char *name)
{
    const char *sieve_path = user_sieve_path(userid);
    char filename[2048];
    char active[2048];
    DIR *mbdir;
    struct dirent *next = NULL;
    struct stat sbuf;
    int is_default = 0;
    int count;

    if (!(mbdir = opendir(sieve_path)))
        return(IMAP_IOERROR);

    while((next = readdir(mbdir)) != NULL) {
        if(!strcmp(next->d_name, ".") || !strcmp(next->d_name, ".."))
            continue;

        snprintf(filename, sizeof(filename), "%s/%s",
                 sieve_path, next->d_name);

        if (stat(filename, &sbuf) < 0)
            continue;

        if (!strcmp(next->d_name, "defaultbc")) {
            if (sbuf.st_mode & S_IFLNK) {
                count = readlink(filename, active, 2047);

                if (count >= 0) {
                    active[count] = '\0';
                    if (!strcmp(active, name))
                        is_default = 1;
                }
            }
            continue;
        }
    }
    closedir(mbdir);

    if (is_default) {
        snprintf(filename, sizeof(filename), "%s/defaultbc", sieve_path);
        unlink(filename);
    }

    snprintf(filename, sizeof(filename), "%s/%s", sieve_path, name);
    unlink(filename);

    sync_log_sieve(userid);

    return(0);
}
