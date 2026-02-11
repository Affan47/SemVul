get_client_mutex(const char* dir) {
    char path[MAXPATHLEN];
    static FILE_LOCK file_lock;

    sprintf(path, "%s/%s", dir, LOCK_FILE_NAME);
    int retval = file_lock.lock(path);
    if (retval == ERR_FCNTL) {
        return ERR_ALREADY_RUNNING;
    } else if (retval) {
        return retval;
    }
#endif
    return 0;
}
