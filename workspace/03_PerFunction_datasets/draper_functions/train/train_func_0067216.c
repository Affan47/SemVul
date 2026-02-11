ntb_store_delete_message_content(struct ntb_store *store,
                                 uint64_t content_id)
{
        struct ntb_store_task *task;

        if (store == NULL)
                store = ntb_store_get_default_or_abort();

        pthread_mutex_lock(&store->mutex);

        task = new_task(store, NTB_STORE_TASK_TYPE_DELETE_MESSAGE_CONTENT);

        task->delete_message_content.id = content_id;

        pthread_mutex_unlock(&store->mutex);
}
