globus_hashtable_copy(
    globus_hashtable_t *                dest_table,
    globus_hashtable_t *                src_table,
    globus_hashtable_copy_func_t        copy_func)
{
    globus_l_hashtable_t *              src_itable;
    globus_l_hashtable_t *              dest_itable;
    int                                 i;
    int                                 size;
    globus_l_hashtable_bucket_entry_t * list;
    globus_l_hashtable_bucket_entry_t   dummy_entry;

    if(dest_table == GLOBUS_NULL ||
        src_table == GLOBUS_NULL ||
        *src_table == GLOBUS_NULL)
    {
        goto error_parm;
    }

    src_itable = *src_table;

    if(globus_hashtable_init(
        dest_table,
        src_itable->size,
        src_itable->hash_func,
        src_itable->keyeq_func) != GLOBUS_SUCCESS)
    {
        goto error_init;
    }

    dest_itable = *dest_table;
    size = src_itable->size;
    dest_itable->load = src_itable->load;

    dummy_entry.next = GLOBUS_NULL;
    list = &dummy_entry;
    for(i = 0; i < size; i++)
    {
        if(src_itable->buckets[i].first)
        {
            globus_l_hashtable_bucket_entry_t * src_entry;
            globus_l_hashtable_bucket_entry_t * dest_entry;
            globus_l_hashtable_bucket_entry_t ** bucket_first;

            src_entry = src_itable->buckets[i].first;
            bucket_first = &list->next;
            do
            {
                dest_entry = (globus_l_hashtable_bucket_entry_t *)
                    globus_memory_pop_node(&dest_itable->memory);
                if(!dest_entry)
                {
                    goto error_alloc;
                }

                if(copy_func)
                {
                    copy_func(
                        &dest_entry->key,
                        &dest_entry->datum,
                        src_entry->key,
                        src_entry->datum);
                }
                else
                {
                    dest_entry->key = src_entry->key;
                    dest_entry->datum = src_entry->datum;
                }

                dest_entry->prev = list;
                dest_entry->next = GLOBUS_NULL;
                list->next = dest_entry;
                list = dest_entry;

                src_entry = src_entry->next;
            } while(
                src_entry && src_entry->prev != src_itable->buckets[i].last);

            dest_itable->buckets[i].first = *bucket_first;
            dest_itable->buckets[i].last = dest_entry;
            dest_itable->last = dest_entry;
        }
    }

    if(dummy_entry.next)
    {
        dest_itable->first = dummy_entry.next;
        dummy_entry.next->prev = GLOBUS_NULL;
    }

    return GLOBUS_SUCCESS;

error_alloc:
    globus_hashtable_destroy(dest_table);

error_init:
    *dest_table = GLOBUS_NULL;

error_parm:
    return GLOBUS_FAILURE;
}
