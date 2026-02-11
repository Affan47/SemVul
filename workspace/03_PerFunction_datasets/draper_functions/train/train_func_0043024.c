find(const char *str, size_t len) const
{
    unsigned int hash;
    CVmHashEntry *entry;


    hash = compute_hash(str, len);


    for (entry = table_[hash] ; entry ; entry = entry->nxt_)
    {

        if (entry->matches(str, len))
            return entry;
    }


    return 0;
}
