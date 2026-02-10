replica_delete_by_name (const char *name)
{
    Object *replica;

    if (name == NULL)
    {
        slapi_log_error(SLAPI_LOG_FATAL, repl_plugin_name, "replica_delete_by_name: "
                        "NULL argument\n");
        return -1;
    }

    if (s_hash == NULL || s_lock == NULL)
    {
        slapi_log_error(SLAPI_LOG_FATAL, repl_plugin_name, "replica_delete_by_name: "
                        "replica hash is not initialized\n");
        return -1;
    }

    slapi_rwlock_wrlock (s_lock);


    replica = (Object*)PL_HashTableLookup(s_hash, name);
    if (replica == NULL)
    {
        slapi_log_error(SLAPI_LOG_FATAL, repl_plugin_name, "replica_delete_by_name: "
                        "replica with name (%s) is not in the hash.\n", name);
        slapi_rwlock_unlock (s_lock);
        return -1;
    }


    PL_HashTableRemove(s_hash, name);


    object_release (replica);

    slapi_rwlock_unlock (s_lock);

    return 0;
}
