cib_fencing_updated(xmlNode * msg, int call_id, int rc, xmlNode * output, void *user_data)
{
    if (rc < pcmk_ok) {
        crm_err("Fencing update %d for %s: failed - %s (%d)",
                call_id, (char *)user_data, pcmk_strerror(rc), rc);
        crm_log_xml_warn(msg, "Failed update");
        abort_transition(INFINITY, tg_shutdown, "CIB update failed", NULL);

    } else {
        crm_info("Fencing update %d for %s: complete", call_id, (char *)user_data);
    }
    free(user_data);
}
