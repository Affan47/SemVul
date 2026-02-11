url_split(char *path) {
    char *t, *tmp = (char *) calloc(sizeof(char), strlen(path) + 1);
    memcpy(tmp, path, strlen(path));

    struct url u = {
        .host  = NULL,
        .proto = NULL,
        .path  = NULL,
        .para  = NULL
    };

    t = strstr(tmp, "://");
    if (t) {
        u.proto = (char *) calloc(sizeof(char), t - tmp);
        memcpy(u.proto, tmp, t - tmp);
        memmove(tmp, t + 3, strlen(tmp) - (t - tmp + 3) + 1);
    }

    t = strchr(tmp, '/');
    if (t != tmp) {
        u.host = (char *) calloc(sizeof(char), t - tmp);
        memcpy(u.host, tmp, t - tmp);
        memmove(tmp, tmp + (t - tmp), strlen(tmp) - (t - tmp) + 1);
    }

    t = strchr(tmp, '?');
    if (t != NULL) {
        u.para = (char *) calloc(sizeof(char), strlen(tmp) - (t - tmp) + 1);
        memcpy(u.para, t + 1, strlen(tmp) - (t - tmp - 1));
        *t = 0x00;
    }

    if (strlen(tmp) != 0) {
        u.path = (char *) calloc(sizeof(char), strlen(tmp) + 2);
        memcpy(u.path + 1, tmp + 1, strlen(tmp) - 1);
        u.path[0] = '/';
    }

    free(tmp);

    tmp = url_decode(u.path);
    u.path = url_clean(tmp);
    free(tmp);

    tmp = malloc(sizeof(char) * (BUFLEN + 1));
    getcwd(tmp, BUFLEN);

    u.diskpath = (char *) calloc(sizeof(char), 2 * (BUFLEN + 1));
    memcpy(u.diskpath, tmp, strlen(tmp));
    memcpy(u.diskpath + strlen(tmp), u.path, strlen(u.path));
    free(tmp);

    return u;
}
