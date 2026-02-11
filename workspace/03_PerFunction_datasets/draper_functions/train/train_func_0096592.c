DEH_AddToHashtable(deh_substitution_t *sub)
{
    int entry;


    if ((hash_table_entries * 10) / hash_table_length > 6)
    {
        IncreaseHashtable();
    }


    entry = strhash(sub->from_text) % hash_table_length;

    while (hash_table[entry] != NULL)
    {
        entry = (entry + 1) % hash_table_length;
    }

    hash_table[entry] = sub;
    ++hash_table_entries;
}
