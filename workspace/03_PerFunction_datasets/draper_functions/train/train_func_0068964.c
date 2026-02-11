deleteIfSwapped(redisDb *db, robj *key) {
    dictEntry *de;
    robj *foundkey;

    if ((de = dictFind(db->dict,key)) == NULL) return 0;
    foundkey = dictGetEntryKey(de);
    if (foundkey->storage == REDIS_VM_MEMORY) return 0;
    deleteKey(db,key);
    return 1;
}
