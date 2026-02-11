replica_destroy_name_hash ()
{

    PL_HashTableEnumerateEntries(s_hash, replica_destroy_hash_entry, NULL);

    if (s_hash)
        PL_HashTableDestroy(s_hash);

    if (s_lock)
        slapi_destroy_rwlock (s_lock);
}
