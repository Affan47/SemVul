art_item_get (const char * file, bool_t blocking)
{
    ArtItem * item = g_hash_table_lookup (art_items, file);

    if (item && item->flag)
    {
        item->refcount ++;
        return item;
    }

    if (! item)
    {
        item = g_slice_new0 (ArtItem);
        g_hash_table_insert (art_items, str_get (file), item);
        item->refcount = 1;

        scan_request (file, SCAN_IMAGE, NULL, request_callback);
    }

    if (! blocking)
        return NULL;

    item->refcount ++;

    while (! item->flag)
        pthread_cond_wait (& cond, & mutex);

    return item;
}
