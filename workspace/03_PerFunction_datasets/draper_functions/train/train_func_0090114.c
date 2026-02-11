boinc_chown(const char* const path, gid_t gid) {
    if (gid) {
        if (chown(path, (uid_t)-1, gid)) {
            return ERR_CHOWN;
        }
    }
    return 0;
}
