Ns_CacheKey(Ns_Entry *entry)
{
    Entry *ePtr = (Entry *) entry;

    return Tcl_GetHashKey(&ePtr->cachePtr->entriesTable, ePtr->hPtr);
}
