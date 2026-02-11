gvplugin_library_load(GVC_t * gvc, char *path)
{
#ifdef ENABLE_LTDL
    lt_dlhandle hndl;
    lt_ptr ptr;
    char *s, *sym;
    int len;
    static char *p;
    static int lenp;
    char *libdir;
    char *suffix = "_LTX_library";

    if (!gvc->common.demand_loading)
        return NULL;

    libdir = gvconfig_libdir(gvc);
    len = strlen(libdir) + 1 + strlen(path) + 1;
    if (len > lenp) {
        lenp = len + 20;
        if (p)
            p = grealloc(p, lenp);
        else
            p = gmalloc(lenp);
    }
#ifdef WIN32
    if (path[1] == ':') {
#else
    if (path[0] == '/') {
#endif
        strcpy(p, path);
    } else {
        strcpy(p, libdir);
        strcat(p, DIRSEP);
        strcat(p, path);
    }

    if (lt_dlinit()) {
        agerr(AGERR, "failed to init libltdl\n");
        return NULL;
    }
    hndl = lt_dlopen(p);
    if (!hndl) {
        agerr(AGWARN, "Could not load \"%s\" - %s\n", p, (char *) lt_dlerror());
        return NULL;
    }
    if (gvc->common.verbose >= 2)
        fprintf(stderr, "Loading %s\n", p);

    s = strrchr(p, DIRSEP[0]);
    len = strlen(s);
#if defined(WIN32) && !defined(__MINGW32__) && !defined(__CYGWIN__)
    if (len < strlen("/gvplugin_x")) {
#else
    if (len < strlen("/libgvplugin_x")) {
#endif
        agerr(AGERR, "invalid plugin path \"%s\"\n", p);
        return NULL;
    }
    sym = gmalloc(len + strlen(suffix) + 1);
#if defined(WIN32) && !defined(__MINGW32__) && !defined(__CYGWIN__)
    strcpy(sym, s + 1);
#else
    strcpy(sym, s + 4);
#endif
#if defined(__CYGWIN__) || defined(__MINGW32__)
    s = strchr(sym, '-');
#else
    s = strchr(sym, '.');
#endif
    strcpy(s, suffix);

    ptr = lt_dlsym(hndl, sym);
    if (!ptr) {
        agerr(AGERR, "failed to resolve %s in %s\n", sym, p);
        free(sym);
        return NULL;
    }
    free(sym);
    return (gvplugin_library_t *) (ptr);
#else
    agerr(AGERR, "dynamic loading not available\n");
    return NULL;
#endif
}
