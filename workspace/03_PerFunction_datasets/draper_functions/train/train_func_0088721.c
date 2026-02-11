project_path(const char *fmt, ...) {
    static char path[MAXPATHLEN];
    va_list ap;

    if (!strlen(project_dir)) {
        char *p = getenv("BOINC_PROJECT_DIR");
        if (p) {
            if (!is_project_dir(p)) {
                fprintf(stderr, "BOINC_PROJECT_DIR env var exists but is not a project dir\n");
                exit(1);
            }
            strlcpy(project_dir, p, sizeof(project_dir));
        } else if (is_project_dir(".")) {
            strcpy(project_dir, ".");
        } else if (is_project_dir("..")) {
            strcpy(project_dir, "..");
        } else {
            fprintf(stderr, "Not in a project directory or subdirectory\n");
            exit(1);
        }
    }

    va_start(ap, fmt);
    snprintf(path, sizeof(path), "%s/", project_dir);
    vsnprintf(path + strlen(path), sizeof(path) - strlen(path), fmt, ap);
    va_end(ap);
    return (const char *)path;
}
