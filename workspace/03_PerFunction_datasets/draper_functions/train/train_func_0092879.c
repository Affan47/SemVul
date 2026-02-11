stonith_recurring_op_helper(gpointer data)
{
    lrmd_cmd_t *cmd = data;
    lrmd_rsc_t *rsc;

    cmd->stonith_recurring_id = 0;

    if (!cmd->rsc_id) {
        return FALSE;
    }

    rsc = g_hash_table_lookup(rsc_list, cmd->rsc_id);

    CRM_ASSERT(rsc != NULL);


    rsc->recurring_ops = g_list_remove(rsc->recurring_ops, cmd);
    rsc->pending_ops = g_list_append(rsc->pending_ops, cmd);
#ifdef HAVE_SYS_TIMEB_H
    ftime(&cmd->t_queue);
#endif
    mainloop_set_trigger(rsc->work);

    return FALSE;
}
