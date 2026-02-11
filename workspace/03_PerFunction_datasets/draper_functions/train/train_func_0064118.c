address_access(ScmHashCore *table,
                             intptr_t key,
                             ScmDictOp op)
{
    u_long hashval, index;
    Entry *e, *p, **buckets = (Entry**)table->buckets;

    ADDRESS_HASH(hashval, key);
    index = HASH2INDEX(table->numBuckets, table->numBucketsLog2, hashval);

    for (e = buckets[index], p = NULL; e; p = e, e = e->next) {
        if (e->key == key) FOUND(table, op, e, p, index);
    }
    NOTFOUND(table, op, key, hashval, index);
}
