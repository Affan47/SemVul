ipc_proxy_dispatch(qb_ipcs_connection_t * c, void *data, size_t size)
{
    uint32_t id = 0;
    uint32_t flags = 0;
    crm_client_t *client = crm_client_get(c);
    crm_client_t *ipc_proxy = crm_client_get_by_id(client->userdata);
    xmlNode *request = NULL;
    xmlNode *msg = NULL;

    if (!ipc_proxy) {
        qb_ipcs_disconnect(client->ipcs);
        return 0;
    }


    request = crm_ipcs_recv(client, data, size, &id, &flags);

    if (!request) {
        return 0;
    }

    CRM_CHECK(client != NULL, crm_err("Invalid client");
              return FALSE);
    CRM_CHECK(client->id != NULL, crm_err("Invalid client: %p", client);
              return FALSE);

    msg = create_xml_node(NULL, T_LRMD_IPC_PROXY);
    crm_xml_add(msg, F_LRMD_IPC_OP, "request");
    crm_xml_add(msg, F_LRMD_IPC_SESSION, client->id);
    crm_xml_add(msg, F_LRMD_IPC_USER, client->user);
    crm_xml_add_int(msg, F_LRMD_IPC_MSG_ID, id);
    crm_xml_add_int(msg, F_LRMD_IPC_MSG_FLAGS, flags);
    add_message_xml(msg, F_LRMD_IPC_MSG, request);
    lrmd_server_send_notify(ipc_proxy, msg);
    free_xml(msg);

    return 0;
}
