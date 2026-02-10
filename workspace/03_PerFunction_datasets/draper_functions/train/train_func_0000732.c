dir_hier_path(
    const char* filename, const char* root, int fanout,
    char* path, bool create
) {
    char dir[256], dirpath[MAXPATHLEN];
    int retval;

    if (fanout==0) {
        sprintf(path, "%s/%s", root, filename);
        return 0;
    }

    filename_hash(filename, fanout, dir);

    sprintf(dirpath, "%s/%s", root, dir);
    if (create) {
        retval = boinc_mkdir(dirpath);
        if (retval && (errno != EEXIST)) {
            fprintf(stderr, "boinc_mkdir(%s): %s: errno %d\n",
                dirpath, boincerror(retval), errno
            );
            return ERR_MKDIR;
        }
    }
    sprintf(path, "%s/%s", dirpath, filename);
    return 0;
}
