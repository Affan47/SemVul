JS_XDRFindClassIdByName(JSXDRState *xdr, const char *name)
{
    uintN i, numclasses;

    numclasses = xdr->numclasses;
    if (numclasses >= 10) {
        JSRegHashEntry *entry;


        if (!xdr->reghash) {
            xdr->reghash =
                JS_NewDHashTable(JS_DHashGetStubOps(), NULL,
                                 sizeof(JSRegHashEntry),
                                 JS_DHASH_DEFAULT_CAPACITY(numclasses));
            if (xdr->reghash) {
                for (i = 0; i < numclasses; i++) {
                    JSClass *clasp = xdr->registry[i];
                    entry = (JSRegHashEntry *)
                        JS_DHashTableOperate((JSDHashTable *) xdr->reghash,
                                             clasp->name, JS_DHASH_ADD);
                    entry->name = clasp->name;
                    entry->index = i;
                }
            }
        }


        if (xdr->reghash) {
            entry = (JSRegHashEntry *)
                JS_DHashTableOperate((JSDHashTable *) xdr->reghash,
                                     name, JS_DHASH_LOOKUP);
            if (JS_DHASH_ENTRY_IS_BUSY(&entry->hdr))
                return CLASS_INDEX_TO_ID(entry->index);
        }
    }


    for (i = 0; i < numclasses; i++) {
        if (!strcmp(name, xdr->registry[i]->name))
            return CLASS_INDEX_TO_ID(i);
    }
    return 0;
}
