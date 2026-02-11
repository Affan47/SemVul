find_keydir_entry(ErlNifEnv* env, bitcask_keydir* keydir, ErlNifBinary* key,
                             entries_hash_t** hash_ptr, khiter_t* itr_ptr,
                             bitcask_keydir_entry** entry_ptr, int iterating)
{

    if (keydir->pending != NULL && !iterating)
    {
        if (get_entries_hash(env, keydir->pending, key, itr_ptr, entry_ptr))
        {
            if (hash_ptr != NULL)
            {
                *hash_ptr = keydir->pending;
            }
            return 1;
        }
    }

    if (get_entries_hash(env, keydir->entries, key, itr_ptr, entry_ptr))
    {
        if (hash_ptr != NULL)
        {
            *hash_ptr = keydir->entries;
        }
        return 1;
    }


    return 0;
}
