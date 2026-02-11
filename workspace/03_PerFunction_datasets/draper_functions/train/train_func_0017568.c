lrmd_tls_recv_reply(lrmd_t * lrmd, int total_timeout, int expected_reply_id, int *disconnected)
{
    lrmd_private_t *native = lrmd->private;
    xmlNode *xml = NULL;
    time_t start = time(NULL);
    const char *msg_type = NULL;
    int reply_id = 0;
    int remaining_timeout = 0;


    if (total_timeout <= 0) {
        total_timeout = 10000;
    }

    while (!xml) {

        xml = crm_remote_parse_buffer(native->remote);
        if (!xml) {

            if (remaining_timeout) {
                remaining_timeout = remaining_timeout - ((time(NULL) - start) * 1000);
            } else {
                remaining_timeout = total_timeout;
            }
            if (remaining_timeout <= 0) {
                return NULL;
            }

            crm_remote_recv(native->remote, remaining_timeout, disconnected);
            xml = crm_remote_parse_buffer(native->remote);
            if (!xml || *disconnected) {
                return NULL;
            }
        }

        CRM_ASSERT(xml != NULL);

        crm_element_value_int(xml, F_LRMD_REMOTE_MSG_ID, &reply_id);
        msg_type = crm_element_value(xml, F_LRMD_REMOTE_MSG_TYPE);

        if (!msg_type) {
            crm_err("Empty msg type received while waiting for reply");
            free_xml(xml);
            xml = NULL;
        } else if (safe_str_eq(msg_type, "notify")) {

            crm_info("queueing notify");
            native->pending_notify = g_list_append(native->pending_notify, xml);
            if (native->process_notify) {
                crm_info("notify trigger set.");
                mainloop_set_trigger(native->process_notify);
            }
            xml = NULL;
        } else if (safe_str_neq(msg_type, "reply")) {

            crm_err("Expected a reply, got %s", msg_type);
            free_xml(xml);
            xml = NULL;
        } else if (reply_id != expected_reply_id) {
            crm_err("Got outdated reply, expected id %d got id %d", expected_reply_id, reply_id);
            free_xml(xml);
            xml = NULL;
        }
    }

    if (native->remote->buffer && native->process_notify) {
        mainloop_set_trigger(native->process_notify);
    }

    return xml;
}
