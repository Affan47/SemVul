ssh_path_expand_tilde(const char *d) {
    char *h = NULL, *r;
    const char *p;
    size_t ld;
    size_t lh = 0;

    if (d[0] != '~') {
        return strdup(d);
    }
    d++;


    p = strchr(d, '/');
    if (p != NULL && p > d) {
#ifdef _WIN32
        return strdup(d);
#else
        struct passwd *pw;
        size_t s = p - d;
        char u[128];

        if (s >= sizeof(u)) {
            return NULL;
        }
        memcpy(u, d, s);
        u[s] = '\0';
        pw = getpwnam(u);
        if (pw == NULL) {
            return NULL;
        }
        ld = strlen(p);
        h = strdup(pw->pw_dir);
#endif
    } else {
        ld = strlen(d);
        p = (char *) d;
        h = ssh_get_user_home_dir();
    }
    if (h == NULL) {
        return NULL;
    }
    lh = strlen(h);

    r = malloc(ld + lh + 1);
    if (r == NULL) {
        SAFE_FREE(h);
        return NULL;
    }

    if (lh > 0) {
        memcpy(r, h, lh);
    }
    SAFE_FREE(h);
    memcpy(r + lh, p, ld + 1);

    return r;
}
