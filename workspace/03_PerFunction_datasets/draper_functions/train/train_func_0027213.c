JimDictPairs(Jim_Obj *dictPtr, int *len)
{
    Jim_HashTable *ht;
    Jim_HashTableIterator htiter;
    Jim_HashEntry *he;
    Jim_Obj **objv;
    int i;

    ht = dictPtr->internalRep.ptr;


    objv = Jim_Alloc((ht->used * 2) * sizeof(Jim_Obj *));
    JimInitHashTableIterator(ht, &htiter);
    i = 0;
    while ((he = Jim_NextHashEntry(&htiter)) != NULL) {
        objv[i++] = (Jim_Obj *)he->key;
        objv[i++] = he->u.val;
    }
    *len = i;
    return objv;
}
