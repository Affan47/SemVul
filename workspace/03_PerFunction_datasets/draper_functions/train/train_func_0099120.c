find_dlobj(const char *path)
{
    dlobj *z = NULL;
    (void)SCM_INTERNAL_MUTEX_LOCK(ldinfo.dso_mutex);
    for (z = ldinfo.dso_list; z; z = z->next) {
        if (strcmp(z->path, path) == 0) break;
    }
    if (z == NULL) {
        z = SCM_NEW(dlobj);
        z->path = path;
        z->loader = NULL;
        z->loaded = FALSE;
        z->initfns = NULL;
        (void)SCM_INTERNAL_MUTEX_INIT(z->mutex);
        (void)SCM_INTERNAL_COND_INIT(z->cv);
        z->next = ldinfo.dso_list;
        ldinfo.dso_list = z;
    }
    (void)SCM_INTERNAL_MUTEX_UNLOCK(ldinfo.dso_mutex);
    return z;
}
