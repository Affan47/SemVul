stonith_connection_failed(void)
{
    GHashTableIter iter;
    GList *cmd_list = NULL;
    GList *cmd_iter = NULL;
    lrmd_rsc_t *rsc = NULL;
    char *key = NULL;

    g_hash_table_iter_init(&iter, rsc_list);
    while (g_hash_table_iter_next(&iter, (gpointer *) & key, (gpointer *) & rsc)) {
        if (safe_str_eq(rsc->class, "stonith")) {
            if (rsc->recurring_ops) {
                cmd_list = g_list_concat(cmd_list, rsc->recurring_ops);
            }
            if (rsc->pending_ops) {
                cmd_list = g_list_concat(cmd_list, rsc->pending_ops);
            }
            rsc->pending_ops = rsc->recurring_ops = NULL;
        }
    }

    if (!cmd_list) {
        return;
    }

    crm_err("STONITH connection failed, finalizing %d pending operations.",
            g_list_length(cmd_list));
    for (cmd_iter = cmd_list; cmd_iter; cmd_iter = cmd_iter->next) {
        stonith_action_complete(cmd_iter->data, -ENOTCONN);
    }
    g_list_free(cmd_list);
}
