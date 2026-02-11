execvp_usingParentPath(const char *file, const char *const argv[])
{
    char expanded_file[PATH_MAX];
    int filelen = strlen(file);
    int sticky_errno = 0;
    const char * const * dirs;

    for (dirs = parentPathv; *dirs; dirs++) {
        const char * dir = *dirs;
        int dirlen = strlen(dir);
        if (filelen + dirlen + 1 >= PATH_MAX) {


            errno = ENAMETOOLONG;
            continue;
        }
        strcpy(expanded_file, dir);
        strcpy(expanded_file + dirlen, file);
        execvp(expanded_file, (char **) argv);


        switch (errno) {
        case EACCES:
            sticky_errno = errno;

        case ENOENT:
        case ENOTDIR:
#ifdef ELOOP
        case ELOOP:
#endif
#ifdef ESTALE
        case ESTALE:
#endif
#ifdef ENODEV
        case ENODEV:
#endif
#ifdef ETIMEDOUT
        case ETIMEDOUT:
#endif
            break;
        default:
            return -1;
        }
    }
    if (sticky_errno != 0)
        errno = sticky_errno;
    return -1;
}
