NewIterator(HashTable *ht)
{
    struct HashTableIterator *result;

    if (ht == NULL) {
        iError.RaiseError("InitIterator",CONTAINER_ERROR_BADARG);
        return NULL;
    }
    result = ht->Allocator->malloc(sizeof(struct HashTableIterator));
    if (result == NULL)
        return NULL;
    result->it.GetNext = GetNext;
    result->it.GetPrevious = GetNext;
    result->it.GetFirst = GetFirst;
    result->it.GetCurrent = GetCurrent;
    result->it.Replace = ReplaceWithIterator;
    result->timestamp = ht->timestamp;
    result->Current = NULL;
    result->ht = ht;
    return &result->it;
}
