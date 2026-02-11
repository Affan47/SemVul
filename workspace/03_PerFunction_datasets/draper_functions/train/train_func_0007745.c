process_lrmd_message(crm_client_t * client, uint32_t id, xmlNode * request)
{
    int rc = pcmk_ok;
    int call_id = 0;
    const char *op = crm_element_value(request, F_LRMD_OPERATION);
    int do_reply = 0;
    int do_notify = 0;

    crm_trace("Processing %s operation from %s", op, client->id);
    crm_element_value_int(request, F_LRMD_CALLID, &call_id);

    if (crm_str_eq(op, CRM_OP_IPC_FWD, TRUE)) {
#ifdef SUPPORT_REMOTE
        ipc_proxy_forward_client(client, request);
#endif
        do_reply = 1;
    } else if (crm_str_eq(op, CRM_OP_REGISTER, TRUE)) {
        rc = process_lrmd_signon(client, id, request);
    } else if (crm_str_eq(op, LRMD_OP_RSC_REG, TRUE)) {
        rc = process_lrmd_rsc_register(client, id, request);
        do_notify = 1;
        do_reply = 1;
    } else if (crm_str_eq(op, LRMD_OP_RSC_INFO, TRUE)) {
        process_lrmd_get_rsc_info(client, id, request);
    } else if (crm_str_eq(op, LRMD_OP_RSC_UNREG, TRUE)) {
        rc = process_lrmd_rsc_unregister(client, id, request);

        if (rc == pcmk_ok || rc == -EINPROGRESS) {
            do_notify = 1;
        }
        do_reply = 1;
    } else if (crm_str_eq(op, LRMD_OP_RSC_EXEC, TRUE)) {
        rc = process_lrmd_rsc_exec(client, id, request);
        do_reply = 1;
    } else if (crm_str_eq(op, LRMD_OP_RSC_CANCEL, TRUE)) {
        rc = process_lrmd_rsc_cancel(client, id, request);
        do_reply = 1;
    } else if (crm_str_eq(op, LRMD_OP_POKE, TRUE)) {
        do_notify = 1;
    } else {
        rc = -EOPNOTSUPP;
        do_reply = 1;
        crm_err("Unknown %s from %s", op, client->name);
        crm_log_xml_warn(request, "UnknownOp");
    }

    crm_debug("Processed %s operation from %s: rc=%d, reply=%d, notify=%d, exit=%d",
              op, client->id, rc, do_reply, do_notify, exit);

    if (do_reply) {
        send_reply(client, rc, id, call_id);
    }

    if (do_notify) {
        send_generic_notify(rc, request);
    }
}
