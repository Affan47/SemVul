_parser_load(struct parser *p, const char *so_path)
{
    lms_plugin_t *(*plugin_open)(void);
    char *errmsg;

    memset(p, 0, sizeof(*p));

    p->dl_handle = dlopen(so_path, RTLD_NOW | RTLD_LOCAL);
    errmsg = dlerror();
    if (errmsg) {
        fprintf(stderr, "ERROR: could not dlopen() %s\n", errmsg);
        return -1;
    }

    plugin_open = dlsym(p->dl_handle, "lms_plugin_open");
    errmsg = dlerror();
    if (errmsg) {
        fprintf(stderr, "ERROR: could not find plugin entry point %s\n",
                errmsg);
        return -2;
    }

    p->so_path = strdup(so_path);
    if (!p->so_path) {
        perror("strdup");
        return -3;
    }

    p->plugin = plugin_open();
    if (!p->plugin) {
        fprintf(stderr, "ERROR: plugin \"%s\" failed to init.\n", so_path);
        return -4;
    }

    return 0;
}
