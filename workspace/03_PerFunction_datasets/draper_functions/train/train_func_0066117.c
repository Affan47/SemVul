JimDictPatternMatch(Jim_Interp *interp, Jim_HashTable *ht, Jim_Obj *patternObjPtr,
    JimDictMatchCallbackType *callback, int type)
{
    Jim_HashEntry *he;
    Jim_Obj *listObjPtr = Jim_NewListObj(interp, NULL, 0);


    Jim_HashTableIterator htiter;
    JimInitHashTableIterator(ht, &htiter);
    while ((he = Jim_NextHashEntry(&htiter)) != NULL) {
        if (patternObjPtr == NULL || JimGlobMatch(Jim_String(patternObjPtr), Jim_String((Jim_Obj *)he->key), 0)) {
            callback(interp, listObjPtr, he, type);
        }
    }

    return listObjPtr;
}
