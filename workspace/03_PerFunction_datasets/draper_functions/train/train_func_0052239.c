SearchTable(JSDHashTable *table, const void *key, JSDHashNumber keyHash,
            JSDHashOperator op)
{
    JSDHashNumber hash1, hash2;
    int hashShift, sizeLog2;
    JSDHashEntryHdr *entry, *firstRemoved;
    JSDHashMatchEntry matchEntry;
    uint32 sizeMask;

    METER(table->stats.searches++);
    JS_ASSERT(!(keyHash & COLLISION_FLAG));


    hashShift = table->hashShift;
    hash1 = HASH1(keyHash, hashShift);
    entry = ADDRESS_ENTRY(table, hash1);


    if (JS_DHASH_ENTRY_IS_FREE(entry)) {
        METER(table->stats.misses++);
        return entry;
    }


    matchEntry = table->ops->matchEntry;
    if (MATCH_ENTRY_KEYHASH(entry, keyHash) && matchEntry(table, entry, key)) {
        METER(table->stats.hits++);
        return entry;
    }


    sizeLog2 = JS_DHASH_BITS - table->hashShift;
    hash2 = HASH2(keyHash, sizeLog2, hashShift);
    sizeMask = JS_BITMASK(sizeLog2);


    firstRemoved = NULL;

    for (;;) {
        if (JS_UNLIKELY(ENTRY_IS_REMOVED(entry))) {
            if (!firstRemoved)
                firstRemoved = entry;
        } else {
            if (op == JS_DHASH_ADD)
                entry->keyHash |= COLLISION_FLAG;
        }

        METER(table->stats.steps++);
        hash1 -= hash2;
        hash1 &= sizeMask;

        entry = ADDRESS_ENTRY(table, hash1);
        if (JS_DHASH_ENTRY_IS_FREE(entry)) {
            METER(table->stats.misses++);
            return (firstRemoved && op == JS_DHASH_ADD) ? firstRemoved : entry;
        }

        if (MATCH_ENTRY_KEYHASH(entry, keyHash) &&
            matchEntry(table, entry, key)) {
            METER(table->stats.hits++);
            return entry;
        }
    }


    return NULL;
}
