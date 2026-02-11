remove_and_update(char *dir_name)
{


    DIR *dir;
    struct dirent *entry;
    pid_t pid;
    pid_t our_pid;
    char *endp;
    char file_name[MAXPATHLEN];


    our_pid = getpid();

    if ((dir = opendir(dir_name)) == NULL) {
        return;
    }

    while((entry = readdir(dir)) != NULL) {


        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0)
            continue;

        pid = (pid_t) strtol(entry->d_name, &endp, 0);
        if (*endp != '\0') {


            continue;
        }
        if (!is_process_up(pid) || pid == our_pid) {
            PR_snprintf(file_name, sizeof(file_name), "%s/%s", dir_name, entry->d_name);
            unlink(file_name);
        }
    }
    closedir(dir);
}
