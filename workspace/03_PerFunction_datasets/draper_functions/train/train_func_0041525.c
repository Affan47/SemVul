Tcl_DeleteHashEntry(entryPtr)
    Tcl_HashEntry *entryPtr;
{
    register Tcl_HashEntry *prevPtr;
    Tcl_HashKeyType *typePtr;
    Tcl_HashTable *tablePtr;
    Tcl_HashEntry **bucketPtr;
    int index;

    tablePtr = entryPtr->tablePtr;
    typePtr = tablePtr->typePtr;


    if (typePtr->hashKeyProc == NULL
	|| typePtr->flags & TCL_HASH_KEY_RANDOMIZE_HASH) {
	index = RANDOM_INDEX (tablePtr, entryPtr->hash);
    } else {
	index = ((unsigned int) entryPtr->hash) & tablePtr->mask;
    }

    bucketPtr = &(tablePtr->buckets[index]);

    if (*bucketPtr == entryPtr) {
	*bucketPtr = entryPtr->nextPtr;
    } else {
	for (prevPtr = *bucketPtr; ; prevPtr = prevPtr->nextPtr) {
	    if (prevPtr == NULL) {

	    }
	    if (prevPtr->nextPtr == entryPtr) {
		prevPtr->nextPtr = entryPtr->nextPtr;
		break;
	    }
	}
    }

    tablePtr->numEntries--;
    if (typePtr->freeEntryProc) {
	typePtr->freeEntryProc (entryPtr);
    } else {
	ckfree((char *) entryPtr);
    }
}
