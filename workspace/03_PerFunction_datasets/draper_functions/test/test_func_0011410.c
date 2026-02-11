te_crm_command(crm_graph_t * graph, crm_action_t * action)
{
    char *counter = NULL;
    xmlNode *cmd = NULL;
    gboolean is_local = FALSE;

    const char *id = NULL;
    const char *task = NULL;
    const char *value = NULL;
    const char *on_node = NULL;
    const char *router_node = NULL;

    gboolean rc = TRUE;
    gboolean no_wait = FALSE;

    id = ID(action->xml);
    task = crm_element_value(action->xml, XML_LRM_ATTR_TASK);
    on_node = crm_element_value(action->xml, XML_LRM_ATTR_TARGET);
    router_node = crm_element_value(action->xml, XML_LRM_ATTR_ROUTER_NODE);

    if (!router_node) {
        router_node = on_node;
    }

    CRM_CHECK(on_node != NULL && strlen(on_node) != 0,
              crm_err("Corrupted command (id=%s) %s: no node", crm_str(id), crm_str(task));
              return FALSE);

    crm_info("Executing crm-event (%s): %s on %s%s%s",
             crm_str(id), crm_str(task), on_node,
             is_local ? " (local)" : "", no_wait ? " - no waiting" : "");

    if (safe_str_eq(router_node, fsa_our_uname)) {
        is_local = TRUE;
    }

    value = crm_meta_value(action->params, XML_ATTR_TE_NOWAIT);
    if (crm_is_true(value)) {
        no_wait = TRUE;
    }

    if (is_local && safe_str_eq(task, CRM_OP_SHUTDOWN)) {

        crm_info("crm-event (%s) is a local shutdown", crm_str(id));
        graph->completion_action = tg_shutdown;
        graph->abort_reason = "local shutdown";
        action->confirmed = TRUE;
        update_graph(graph, action);
        trigger_graph();
        return TRUE;

    } else if (safe_str_eq(task, CRM_OP_SHUTDOWN)) {
        crm_node_t *peer = crm_get_peer(0, router_node);
        crm_update_peer_expected(__FUNCTION__, peer, CRMD_JOINSTATE_DOWN);
    }

    cmd = create_request(task, action->xml, router_node, CRM_SYSTEM_CRMD, CRM_SYSTEM_TENGINE, NULL);

    counter =
        generate_transition_key(transition_graph->id, action->id, get_target_rc(action), te_uuid);
    crm_xml_add(cmd, XML_ATTR_TRANSITION_KEY, counter);

    rc = send_cluster_message(crm_get_peer(0, router_node), crm_msg_crmd, cmd, TRUE);
    free(counter);
    free_xml(cmd);

    if (rc == FALSE) {
        crm_err("Action %d failed: send", action->id);
        return FALSE;

    } else if (no_wait) {
        action->confirmed = TRUE;
        update_graph(graph, action);
        trigger_graph();

    } else {
        if (action->timeout <= 0) {
            crm_err("Action %d: %s on %s had an invalid timeout (%dms).  Using %dms instead",
                    action->id, task, on_node, action->timeout, graph->network_delay);
            action->timeout = graph->network_delay;
        }
        te_start_action_timer(graph, action);
    }

    return TRUE;
}
