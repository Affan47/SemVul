send_msg_via_ipc(xmlNode * msg, const char *sys)
{
    gboolean send_ok = TRUE;
    crm_client_t *client_channel = crm_client_get_by_id(sys);

    if (crm_element_value(msg, F_CRM_HOST_FROM) == NULL) {
        crm_xml_add(msg, F_CRM_HOST_FROM, fsa_our_uname);
    }

    if (client_channel != NULL) {

        send_ok = crm_ipcs_send(client_channel, 0, msg, TRUE);

    } else if (sys != NULL && strcmp(sys, CRM_SYSTEM_TENGINE) == 0) {
        xmlNode *data = get_message_xml(msg, F_CRM_DATA);

        process_te_message(msg, data);

    } else if (sys != NULL && strcmp(sys, CRM_SYSTEM_LRMD) == 0) {
        fsa_data_t fsa_data;
        ha_msg_input_t fsa_input;

        fsa_input.msg = msg;
        fsa_input.xml = get_message_xml(msg, F_CRM_DATA);

        fsa_data.id = 0;
        fsa_data.actions = 0;
        fsa_data.data = &fsa_input;
        fsa_data.fsa_input = I_MESSAGE;
        fsa_data.fsa_cause = C_IPC_MESSAGE;
        fsa_data.origin = __FUNCTION__;
        fsa_data.data_type = fsa_dt_ha_msg;

#ifdef FSA_TRACE
        crm_trace("Invoking action A_LRM_INVOKE (%.16llx)", A_LRM_INVOKE);
#endif
        do_lrm_invoke(A_LRM_INVOKE, C_IPC_MESSAGE, fsa_state, I_MESSAGE, &fsa_data);

    } else if (sys != NULL && crmd_is_proxy_session(sys)) {
        crmd_proxy_send(sys, msg);

    } else {
        crm_err("Unknown Sub-system (%s)... discarding message.", crm_str(sys));
        send_ok = FALSE;
    }

    return send_ok;
}
