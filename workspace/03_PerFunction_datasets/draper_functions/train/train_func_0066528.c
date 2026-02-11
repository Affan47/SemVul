unloadObj( pathchar *path )
{
    ObjectCode *oc, *prev;
    HsBool unloadedAnyObj = HS_BOOL_FALSE;

    ASSERT(symhash != NULL);
    ASSERT(objects != NULL);

    initLinker();

    prev = NULL;
    for (oc = objects; oc; prev = oc, oc = oc->next) {
        if (!pathcmp(oc->fileName,path)) {


            {
                int i;
                for (i = 0; i < oc->n_symbols; i++) {
                   if (oc->symbols[i] != NULL) {
                       removeStrHashTable(symhash, oc->symbols[i], NULL);
                   }
                }
            }

            if (prev == NULL) {
                objects = oc->next;
            } else {
                prev->next = oc->next;
            }


            stgFree(oc->fileName);
            stgFree(oc->archiveMemberName);
            stgFree(oc->symbols);
            stgFree(oc->sections);
            stgFree(oc);


            unloadedAnyObj = HS_BOOL_TRUE;
        }
    }

    if (unloadedAnyObj) {
        return 1;
    }
    else {
        errorBelch("unloadObj: can't find `%" PATH_FMT "' to unload", path);
        return 0;
    }
}
