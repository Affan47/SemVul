lg_addTokenKeyByHandle(SDB *sdb, CK_OBJECT_HANDLE handle, SECItem *key)
{
    PLHashEntry *entry;
    SECItem *item;
    PLHashTable *hashTable= lg_GetHashTable(sdb);

    item = SECITEM_DupItem(key);
    if (item == NULL) {
	return SECFailure;
    }
    entry = PL_HashTableAdd(hashTable,(void *)handle,item);
    if (entry == NULL) {
	SECITEM_FreeItem(item,PR_TRUE);
	return SECFailure;
    }
    return SECSuccess;
}
