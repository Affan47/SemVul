log_operation(async_command_t * cmd, int rc, int pid, const char *next, const char *output)
{
    if (rc == 0) {
        next = NULL;
    }

    if (cmd->victim != NULL) {
        do_crm_log(rc == 0 ? LOG_NOTICE : LOG_ERR,
                   "Operation '%s' [%d] (call %d from %s) for host '%s' with device '%s' returned: %d (%s)%s%s",
                   cmd->action, pid, cmd->id, cmd->client_name, cmd->victim, cmd->device, rc,
                   pcmk_strerror(rc), next ? ". Trying: " : "", next ? next : "");
    } else {
        do_crm_log_unlikely(rc == 0 ? LOG_DEBUG : LOG_NOTICE,
                            "Operation '%s' [%d] for device '%s' returned: %d (%s)%s%s",
                            cmd->action, pid, cmd->device, rc, pcmk_strerror(rc),
                            next ? ". Trying: " : "", next ? next : "");
    }

    if (output) {

        char *prefix = g_strdup_printf("%s:%d", cmd->device, pid);

        crm_log_output(rc == 0 ? LOG_INFO : LOG_WARNING, prefix, output);
        g_free(prefix);
    }
}
