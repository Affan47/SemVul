cibmon_diff(const char *event, xmlNode * msg)
{
    int rc = -1;
    const char *op = NULL;
    unsigned int log_level = LOG_INFO;

    xmlNode *diff = NULL;
    xmlNode *cib_last = NULL;
    xmlNode *update = get_message_xml(msg, F_CIB_UPDATE);

    if (msg == NULL) {
        crm_err("NULL update");
        return;
    }

    crm_element_value_int(msg, F_CIB_RC, &rc);
    op = crm_element_value(msg, F_CIB_OPERATION);
    diff = get_message_xml(msg, F_CIB_UPDATE_RESULT);

    if (rc < pcmk_ok) {
        log_level = LOG_WARNING;
        do_crm_log(log_level, "[%s] %s ABORTED: %s", event, op, pcmk_strerror(rc));
        return;
    }

    if (log_diffs) {
        log_cib_diff(log_level, diff, op);
    }

    if (log_updates && update != NULL) {
        crm_log_xml_trace(update, "raw_update");
    }

    if (cib_copy != NULL) {
        cib_last = cib_copy;
        cib_copy = NULL;
        rc = cib_process_diff(op, cib_force_diff, NULL, NULL, diff, cib_last, &cib_copy, NULL);

        if (rc != pcmk_ok) {
            crm_debug("Update didn't apply, requesting full copy: %s", pcmk_strerror(rc));
            free_xml(cib_copy);
            cib_copy = NULL;
        }
    }

    if (cib_copy == NULL) {
        cib_copy = get_cib_copy(cib);
    }

    free_xml(cib_last);
}
