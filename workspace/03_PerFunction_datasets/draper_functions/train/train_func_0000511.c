ntb_store_save_message(struct ntb_store *store,
                       int64_t timestamp,
                       struct ntb_key *from_key,
                       const char *from_address,
                       struct ntb_key *to_key,
                       struct ntb_blob *blob)
{
        struct ntb_store_task *task;

        if (store == NULL)
                store = ntb_store_get_default_or_abort();

        pthread_mutex_lock(&store->mutex);

        task = new_task(store, NTB_STORE_TASK_TYPE_SAVE_MESSAGE);

        task->save_message.timestamp = timestamp;
        if (from_key)
                task->save_message.from_key = ntb_key_ref(from_key);
        else
                task->save_message.from_key = NULL;
        strcpy(task->save_message.from_address, from_address);
        task->save_message.to_key = ntb_key_ref(to_key);
        task->save_message.blob = ntb_blob_ref(blob);

        pthread_mutex_unlock(&store->mutex);
}
