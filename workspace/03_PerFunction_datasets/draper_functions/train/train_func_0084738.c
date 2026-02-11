get_shadow_file(const char *suffix)
{
    char *cib_home = NULL;
    char *fullname = NULL;
    char *name = crm_concat("shadow", suffix, '.');
    const char *dir = getenv("CIB_shadow_dir");

    if (dir == NULL) {
        uid_t uid = geteuid();
        struct passwd *pwent = getpwuid(uid);
        const char *user = NULL;

        if (pwent) {
            user = pwent->pw_name;
        } else {
            crm_perror(LOG_ERR, "Cannot get password entry for uid: %d", uid);
            user = getenv("USER");
        }

        if (safe_str_eq(user, "root") || safe_str_eq(user, CRM_DAEMON_USER)) {
            dir = CRM_CONFIG_DIR;

        } else {
            const char *home = NULL;

            if ((home = getenv("HOME")) == NULL) {
                if (pwent) {
                    home = pwent->pw_dir;
                }
            }

            if ((dir = getenv("TMPDIR")) == NULL) {
                dir = "/tmp";
            }
            if (home && home[0] == '/') {
                int rc = 0;

                cib_home = crm_concat(home, ".cib", '/');

                rc = mkdir(cib_home, 0700);
                if (rc < 0 && errno != EEXIST) {
                    crm_perror(LOG_ERR, "Couldn't create user-specific shadow directory: %s",
                               cib_home);
                    errno = 0;

                } else {
                    dir = cib_home;
                }
            }
        }
    }

    fullname = crm_concat(dir, name, '/');
    free(cib_home);
    free(name);

    return fullname;
}
