JS_DHashTableEnumerate(JSDHashTable *table, JSDHashEnumerator etor, void *arg)
{
    char *entryAddr, *entryLimit;
    uint32 i, capacity, entrySize, ceiling;
    JSBool didRemove;
    JSDHashEntryHdr *entry;
    JSDHashOperator op;

    INCREMENT_RECURSION_LEVEL(table);

    entryAddr = table->entryStore;
    entrySize = table->entrySize;
    capacity = JS_DHASH_TABLE_SIZE(table);
    entryLimit = entryAddr + capacity * entrySize;
    i = 0;
    didRemove = JS_FALSE;
    while (entryAddr < entryLimit) {
        entry = (JSDHashEntryHdr *)entryAddr;
        if (ENTRY_IS_LIVE(entry)) {
            op = etor(table, entry, i++, arg);
            if (op & JS_DHASH_REMOVE) {
                METER(table->stats.removeEnums++);
                JS_DHashTableRawRemove(table, entry);
                didRemove = JS_TRUE;
            }
            if (op & JS_DHASH_STOP)
                break;
        }
        entryAddr += entrySize;
    }

    JS_ASSERT(!didRemove || RECURSION_LEVEL(table) == 1);


    if (didRemove &&
        (table->removedCount >= capacity >> 2 ||
         (capacity > JS_DHASH_MIN_SIZE &&
          table->entryCount <= MIN_LOAD(table, capacity)))) {
        METER(table->stats.enumShrinks++);
        capacity = table->entryCount;
        capacity += capacity >> 1;
        if (capacity < JS_DHASH_MIN_SIZE)
            capacity = JS_DHASH_MIN_SIZE;

        JS_CEILING_LOG2(ceiling, capacity);
        ceiling -= JS_DHASH_BITS - table->hashShift;

        (void) ChangeTable(table, ceiling);
    }

    DECREMENT_RECURSION_LEVEL(table);

    return i;
}
