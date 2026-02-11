dlget (void *handle, const char *name, int *err)
{
    void *p = gretl_dlsym(handle, name);

    if (p == NULL) {
	fprintf(stderr, "dlget: couldn't find '%s'\n", name);
	*err += 1;
    }

    return p;
}
