module_filename(struct augeas *aug, const char *modname) {
    char *dir = NULL;
    char *filename = NULL;
    char *name = module_basename(modname);

    while ((dir = argz_next(aug->modpathz, aug->nmodpath, dir)) != NULL) {
        int len = strlen(name) + strlen(dir) + 2;
        struct stat st;

        if (REALLOC_N(filename, len) == -1)
            goto error;
        sprintf(filename, "%s/%s", dir, name);
        if (stat(filename, &st) == 0)
            goto done;
    }
 error:
    FREE(filename);
 done:
    free(name);
    return filename;
}
