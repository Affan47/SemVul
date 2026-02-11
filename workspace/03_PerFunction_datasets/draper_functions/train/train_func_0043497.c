get(const Identifier &name) const
{
    assert(!name.isNull());

    UString::Rep *rep = name._ustring.rep();

    if (!m_usingTable) {
#if USE_SINGLE_ENTRY
        UString::Rep *key = m_singleEntryKey;
        if (rep == key)
            return m_u.singleEntryValue;
#endif
        return 0;
    }

    unsigned h = rep->hash();
    int sizeMask = m_u.table->sizeMask;
    Entry *entries = m_u.table->entries;
    int i = h & sizeMask;
    int k = 0;
#if DUMP_STATISTICS
    ++numProbes;
    numCollisions += entries[i].key && entries[i].key != rep;
#endif
    while (UString::Rep *key = entries[i].key) {
        if (rep == key)
            return entries[i].value;
        if (k == 0)
            k = 1 | (h % sizeMask);
        i = (i + k) & sizeMask;
#if DUMP_STATISTICS
        ++numRehashes;
#endif
    }
    return 0;
}
