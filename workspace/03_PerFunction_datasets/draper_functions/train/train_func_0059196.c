find_parent(const ap_directive_t *dirp,
                                          const char *what)
{
    while (dirp->parent != NULL) {
        dirp = dirp->parent;


        if (strcasecmp(dirp->directive, what) == 0)
            return dirp;
    }

    return NULL;
}
