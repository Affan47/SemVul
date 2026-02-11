values_destroy()
{
    action_destroy(values.action_shutdown);
    action_destroy(values.action_restart);
    action_destroy(values.action_logout);

    if(values.command_before_action != NULL)
        g_free(values.command_before_action);

    if(values.time_when_notify.nb != NULL)
        g_free(values.time_when_notify.nb);

    if(values.time_when_notify.time != NULL)
        g_free(values.time_when_notify.time);

    memset(&values, 0, sizeof(struct t_values));
}
