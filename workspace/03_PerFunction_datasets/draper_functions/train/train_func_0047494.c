trigger_callback(registered_cb_item_t *cb, pending_pids_item_t *pending)
{
    assert(cb->pid == pending->pid);

    OPAL_THREAD_UNLOCK(&mutex);
    cb->callback(cb->pid, pending->status, cb->data);
    OPAL_THREAD_LOCK(&mutex);

    opal_list_remove_item(&pending_pids, (opal_list_item_t*) pending);
    opal_list_remove_item(&registered_cb, (opal_list_item_t*) cb);
}
