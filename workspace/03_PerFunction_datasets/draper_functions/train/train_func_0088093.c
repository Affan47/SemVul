sge_htable_lookup(htable table, const void* key, const void** data)
{
    Bucket *bucket;

    for (bucket = table->table[table->hash_func(key) & table->mask];
         bucket;
         bucket = bucket->next) {
        if(table->compare_func(bucket->key, key) == 0) {
            *data = (void *)bucket->data;
            return True;
        }
    }
    return False;
}
