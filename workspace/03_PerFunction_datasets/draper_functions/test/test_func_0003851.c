recurring_action_timer(gpointer data)
{
    svc_action_t *op = data;

    crm_debug("Scheduling another invokation of %s", op->id);


    free(op->stdout_data);
    op->stdout_data = NULL;
    free(op->stderr_data);
    op->stderr_data = NULL;
    op->opaque->repeat_timer = 0;

    services_action_async(op, NULL);
    return FALSE;
}
