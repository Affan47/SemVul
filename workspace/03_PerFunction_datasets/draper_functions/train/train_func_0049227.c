sync_sieve_list_generate(const char *userid)
{
    struct sync_sieve_list *list = sync_sieve_list_create();
    const char *sieve_path = user_sieve_path(userid);
    char filename[2048];
    char active[2048];
    DIR *mbdir;
    struct dirent *next = NULL;
    struct stat sbuf;
    int count;


    if (!(mbdir = opendir(sieve_path)))
        return(list);

    active[0] = '\0';
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
                } else {

                }
            }
            continue;
        }
        sync_sieve_list_add(list, next->d_name, sbuf.st_mtime, 0);
    }
    closedir(mbdir);

    if (active[0])
        sync_sieve_list_set_active(list, active);

    return list;
}
