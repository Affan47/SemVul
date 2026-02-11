get(HASH_TYPE hash)
{
    if (data[hash % TRANSPOSITION_TABLE_SIZE].first == hash)
        return &data[hash % TRANSPOSITION_TABLE_SIZE].second;
    else
        return NULL;
}
