ssh_get_local_username(void) {
    struct passwd pwd;
    struct passwd *pwdbuf;
    char buf[NSS_BUFLEN_PASSWD];
    char *name;
    int rc;

    rc = getpwuid_r(getuid(), &pwd, buf, NSS_BUFLEN_PASSWD, &pwdbuf);
    if (rc != 0) {
        return NULL;
    }

    name = strdup(pwd.pw_name);

    if (name == NULL) {
        return NULL;
    }

    return name;
}
