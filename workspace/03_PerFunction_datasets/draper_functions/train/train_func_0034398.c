ht_set_fa(hashtable *ht, void *key, void *data,
        void (*free_key)(void*), void (*free_data)(void*),
        const void *hash_arg, const void *cmp_arg)
{
    void *data_old;

    if (!ht || !key || !data)
        return HT_ERROR;

    data_old = ht_remove_fa(ht, key, free_key, hash_arg, cmp_arg);
    if (data_old)
    {
        FREE_DATA(data_old);
    }

    return ht_insert_a(ht, key, data, hash_arg, cmp_arg);
}
