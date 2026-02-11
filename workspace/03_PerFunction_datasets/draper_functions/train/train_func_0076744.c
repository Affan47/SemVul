_dl_dlopen(const char *path)
{
    void *result;

    BD_DEBUG(DBG_FILE, "searching for library '%s' ...\n", path);

    result = dlopen(path, RTLD_LAZY);

    if (!result) {
        BD_DEBUG(DBG_FILE, "can't open library '%s': %s\n", path, dlerror());
    }

    return result;
}
