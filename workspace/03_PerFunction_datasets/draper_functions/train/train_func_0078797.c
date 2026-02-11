store_to_s(Store *store)
{
    struct FileNameListArg fnl;
    char *buf, *b;
    int i;
    fnl.count = 0;
    fnl.size = 16;
    fnl.total_len = 10;
    fnl.files = ALLOC_N(char *, 16);

    store->each(store, &add_file_name, &fnl);
    qsort(fnl.files, fnl.count, sizeof(char *), &scmp);
    b = buf = ALLOC_N(char, fnl.total_len);

    for (i = 0; i < fnl.count; i++) {
        char *fn = fnl.files[i];
        int len = strlen(fn);
        memcpy(b, fn, len);
        b += len;
        *b++ = '\n';
        free(fn);
    }
    *b = '\0';
    free(fnl.files);

    return buf;
}
