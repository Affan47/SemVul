tempnam_local(const char *dir, const char *pfx) {
    char *name;
    pid_t pid = getpid();


#ifndef MAXPATHLEN
#define MAXPATHLEN 4096
#endif

    if (!pfx)
        pfx = "cftmp.";


    if (dir != NULL) {
        if (!(name = (char *)malloc(MAXPATHLEN)))
            return(NULL);
        do {
#ifdef HAVE_SNPRINTF
            (void)snprintf(name, MAXPATHLEN, "%s/%s%x.%u", dir, pfx, (unsigned int)pid, curtmp);
#else
            (void)sprintf(name, "%s/%s%x%u", dir, pfx, (unsigned int)pid, curtmp);
#endif
            curtmp++;
        } while (access(name, F_OK) != -1);
        return(name);
    }
    return(NULL);
}
