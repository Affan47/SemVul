lrmd_copy_event(lrmd_event_data_t * event)
{
    lrmd_event_data_t *copy = NULL;

    copy = calloc(1, sizeof(lrmd_event_data_t));


    memcpy(copy, event, sizeof(lrmd_event_data_t));

    copy->rsc_id = event->rsc_id ? strdup(event->rsc_id) : NULL;
    copy->op_type = event->op_type ? strdup(event->op_type) : NULL;
    copy->user_data = event->user_data ? strdup(event->user_data) : NULL;
    copy->output = event->output ? strdup(event->output) : NULL;
    copy->remote_nodename = event->remote_nodename ? strdup(event->remote_nodename) : NULL;

    if (event->params) {
        copy->params = g_hash_table_new_full(crm_str_hash,
                                             g_str_equal, g_hash_destroy_str, g_hash_destroy_str);

        if (copy->params != NULL) {
            g_hash_table_foreach(event->params, dup_attr, copy->params);
        }
    }

    return copy;
}
