crm_enable_blackbox(int nsig)
{
    if (blackbox_file_prefix == NULL) {
        pid_t pid = getpid();

        blackbox_file_prefix = malloc(NAME_MAX);
        snprintf(blackbox_file_prefix, NAME_MAX, "%s/%s-%d", CRM_BLACKBOX_DIR, crm_system_name,
                 pid);
    }

    if (qb_log_ctl(QB_LOG_BLACKBOX, QB_LOG_CONF_STATE_GET, 0) != QB_LOG_STATE_ENABLED) {
        qb_log_ctl(QB_LOG_BLACKBOX, QB_LOG_CONF_SIZE, 5 * 1024 * 1024);
        qb_log_ctl(QB_LOG_BLACKBOX, QB_LOG_CONF_ENABLED, QB_TRUE);

        crm_notice("Initiated blackbox recorder: %s", blackbox_file_prefix);


        crm_signal(SIGSEGV, crm_trigger_blackbox);
        crm_signal(SIGABRT, crm_trigger_blackbox);
        crm_signal(SIGILL,  crm_trigger_blackbox);
        crm_signal(SIGBUS,  crm_trigger_blackbox);

        crm_update_callsites();

        blackbox_trigger = qb_log_custom_open(blackbox_logger, NULL, NULL, NULL);
        qb_log_ctl(blackbox_trigger, QB_LOG_CONF_ENABLED, QB_TRUE);
        crm_trace("Trigger: %d is %d %d", blackbox_trigger,
                  qb_log_ctl(blackbox_trigger, QB_LOG_CONF_STATE_GET, 0), QB_LOG_STATE_ENABLED);

        crm_update_callsites();
    }
}
