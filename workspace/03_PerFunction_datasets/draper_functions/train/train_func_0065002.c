notify_deleted(lrm_state_t * lrm_state, ha_msg_input_t * input, const char *rsc_id, int rc)
{
    lrmd_event_data_t *op = NULL;
    const char *from_sys = crm_element_value(input->msg, F_CRM_SYS_FROM);
    const char *from_host = crm_element_value(input->msg, F_CRM_HOST_FROM);

    crm_info("Notifying %s on %s that %s was%s deleted",
             from_sys, from_host, rsc_id, rc == pcmk_ok ? "" : " not");

    op = construct_op(lrm_state, input->xml, rsc_id, CRMD_ACTION_DELETE);
    CRM_ASSERT(op != NULL);

    if (rc == pcmk_ok) {
        op->op_status = PCMK_LRM_OP_DONE;
        op->rc = PCMK_EXECRA_OK;
    } else {
        op->op_status = PCMK_LRM_OP_ERROR;
        op->rc = PCMK_EXECRA_UNKNOWN_ERROR;
    }

    send_direct_ack(from_host, from_sys, NULL, op, rsc_id);
    lrmd_free_event(op);

    if (safe_str_neq(from_sys, CRM_SYSTEM_TENGINE)) {

        time_t now = time(NULL);
        char *now_s = crm_itoa(now);

        crm_debug("Triggering a refresh after %s deleted %s from the LRM", from_sys, rsc_id);

        update_attr_delegate(fsa_cib_conn, cib_none, XML_CIB_TAG_CRMCONFIG, NULL, NULL, NULL, NULL,
                             "last-lrm-refresh", now_s, FALSE, NULL);

        free(now_s);
    }
}
