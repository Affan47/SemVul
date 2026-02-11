find_importinfo(msft_typelib_t *typelib, const char *name)
{
    importlib_t *importlib;
    int i;

    chat("search importlib %s\n", name);

    if(!name)
        return NULL;

    LIST_FOR_EACH_ENTRY( importlib, &typelib->typelib->importlibs, importlib_t, entry )
    {
        for(i=0; i < importlib->ntypeinfos; i++) {
            if(!strcmp(name, importlib->importinfos[i].name)) {
                chat("Found %s in importlib.\n", name);
                return importlib->importinfos+i;
            }
        }
    }

    return NULL;
}
