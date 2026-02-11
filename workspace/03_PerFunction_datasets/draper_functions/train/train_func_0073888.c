services_action_async(svc_action_t * op, void (*action_callback) (svc_action_t *))
{
    if (action_callback) {
        op->opaque->callback = action_callback;
    }

    if (recurring_actions == NULL) {
        recurring_actions = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, NULL);
    }

    if (op->interval > 0) {
        g_hash_table_replace(recurring_actions, op->id, op);
    }
#if SUPPORT_UPSTART
    if (strcasecmp(op->standard, "upstart") == 0) {
        return upstart_job_exec(op, FALSE);
    }
#endif
#if SUPPORT_SYSTEMD
    if (strcasecmp(op->standard, "systemd") == 0) {
        return systemd_unit_exec(op, FALSE);
    }
#endif
    return services_os_action_execute(op, FALSE);
}
