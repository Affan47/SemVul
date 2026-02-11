cancel_all_recurring(lrmd_rsc_t * rsc, const char *client_id)
{
    GList *cmd_list = NULL;
    GList *cmd_iter = NULL;


    if (rsc->recurring_ops) {
        cmd_list = g_list_concat(cmd_list, g_list_copy(rsc->recurring_ops));
    }
    if (rsc->pending_ops) {
        cmd_list = g_list_concat(cmd_list, g_list_copy(rsc->pending_ops));
    }
    if (!cmd_list) {
        return;
    }

    for (cmd_iter = cmd_list; cmd_iter; cmd_iter = cmd_iter->next) {
        lrmd_cmd_t *cmd = cmd_iter->data;

        if (cmd->interval == 0) {
            continue;
        }

        if (client_id && safe_str_neq(cmd->client_id, client_id)) {
            continue;
        }

        cancel_op(rsc->rsc_id, cmd->action, cmd->interval);
    }

    g_list_free(cmd_list);
}
