stonith_api_signon(stonith_t * stonith, const char *name, int *stonith_fd)
{
    int rc = pcmk_ok;
    stonith_private_t *native = stonith->private;

    static struct ipc_client_callbacks st_callbacks = {
        .dispatch = stonith_dispatch_internal,
        .destroy = stonith_connection_destroy
    };

    crm_trace("Connecting command channel");

    stonith->state = stonith_connected_command;
    if (stonith_fd) {

        native->ipc = crm_ipc_new("stonith-ng", 0);

        if (native->ipc && crm_ipc_connect(native->ipc)) {
            *stonith_fd = crm_ipc_get_fd(native->ipc);

        } else if (native->ipc) {
            rc = -ENOTCONN;
        }

    } else {

        native->source =
            mainloop_add_ipc_client("stonith-ng", G_PRIORITY_MEDIUM, 0, stonith, &st_callbacks);
        native->ipc = mainloop_get_ipc_client(native->source);
    }

    if (native->ipc == NULL) {
        crm_debug("Could not connect to the Stonith API");
        rc = -ENOTCONN;
    }

    if (rc == pcmk_ok) {
        xmlNode *reply = NULL;
        xmlNode *hello = create_xml_node(NULL, "stonith_command");

        crm_xml_add(hello, F_TYPE, T_STONITH_NG);
        crm_xml_add(hello, F_STONITH_OPERATION, CRM_OP_REGISTER);
        crm_xml_add(hello, F_STONITH_CLIENTNAME, name);
        rc = crm_ipc_send(native->ipc, hello, crm_ipc_client_response, -1, &reply);

        if (rc < 0) {
            crm_perror(LOG_DEBUG, "Couldn't complete registration with the fencing API: %d", rc);
            rc = -ECOMM;

        } else if (reply == NULL) {
            crm_err("Did not receive registration reply");
            rc = -EPROTO;

        } else {
            const char *msg_type = crm_element_value(reply, F_STONITH_OPERATION);
            const char *tmp_ticket = crm_element_value(reply, F_STONITH_CLIENTID);

            if (safe_str_neq(msg_type, CRM_OP_REGISTER)) {
                crm_err("Invalid registration message: %s", msg_type);
                crm_log_xml_err(reply, "Bad reply");
                rc = -EPROTO;

            } else if (tmp_ticket == NULL) {
                crm_err("No registration token provided");
                crm_log_xml_err(reply, "Bad reply");
                rc = -EPROTO;

            } else {
                crm_trace("Obtained registration token: %s", tmp_ticket);
                native->token = strdup(tmp_ticket);
                rc = pcmk_ok;
            }
        }

        free_xml(reply);
        free_xml(hello);
    }

    if (rc == pcmk_ok) {
#if HAVE_MSGFROMIPC_TIMEOUT
        stonith->call_timeout = MAX_IPC_DELAY;
#endif
        crm_debug("Connection to STONITH successful");
        return pcmk_ok;
    }

    crm_debug("Connection to STONITH failed: %s", pcmk_strerror(rc));
    stonith->cmds->disconnect(stonith);
    return rc;
}
