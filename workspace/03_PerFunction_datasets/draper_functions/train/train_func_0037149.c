init_loadpath(struct augeas *aug, const char *loadpath) {
    int r;

    aug->modpathz = NULL;
    aug->nmodpath = 0;
    if (loadpath != NULL) {
        r = argz_add_sep(&aug->modpathz, &aug->nmodpath,
                         loadpath, PATH_SEP_CHAR);
        if (r != 0)
            return -1;
    }
    char *env = getenv(AUGEAS_LENS_ENV);
    if (env != NULL) {
        r = argz_add_sep(&aug->modpathz, &aug->nmodpath,
                         env, PATH_SEP_CHAR);
        if (r != 0)
            return -1;
    }
    if (!(aug->flags & AUG_NO_STDINC)) {
        r = argz_add(&aug->modpathz, &aug->nmodpath, AUGEAS_LENS_DIR);
        if (r != 0)
            return -1;
        r = argz_add(&aug->modpathz, &aug->nmodpath,
                     AUGEAS_LENS_DIST_DIR);
        if (r != 0)
            return -1;
    }

    if (aug->nmodpath > 0) {
        argz_stringify(aug->modpathz, aug->nmodpath, PATH_SEP_CHAR);
        char *s, *t;
        const char *e = aug->modpathz + strlen(aug->modpathz);
        for (s = aug->modpathz, t = aug->modpathz; s < e; s++) {
            char *p = s;
            if (*p == '/') {
                while (*p == '/') p += 1;
                if (*p == '\0' || *p == PATH_SEP_CHAR)
                    s = p;
            }
            if (t != s)
                *t++ = *s;
            else
                t += 1;
        }
        if (t != s) {
            *t = '\0';
        }
        s = aug->modpathz;
        aug->modpathz = NULL;
        r = argz_create_sep(s, PATH_SEP_CHAR, &aug->modpathz,
                            &aug->nmodpath);
        free(s);
        if (r != 0)
            return -1;
    }
    return 0;
}
