schedule_stonith_command(async_command_t * cmd, stonith_device_t * device)
{
    CRM_CHECK(cmd != NULL, return);
    CRM_CHECK(device != NULL, return);

    if (cmd->device) {
        free(cmd->device);
    }

    if (device->include_nodeid && cmd->victim) {
        crm_node_t *node = crm_get_peer(0, cmd->victim);

        cmd->victim_nodeid = node->id;
    }

    cmd->device = strdup(device->id);
    cmd->timeout = get_action_timeout(device, cmd->action, cmd->default_timeout);

    if (cmd->remote_op_id) {
        crm_debug("Scheduling %s on %s for remote peer %s with op id (%s) (timeout=%ds)",
                  cmd->action, device->id, cmd->origin, cmd->remote_op_id, cmd->timeout);
    } else {
        crm_debug("Scheduling %s on %s for %s (timeout=%ds)",
                  cmd->action, device->id, cmd->client, cmd->timeout);
    }

    device->pending_ops = g_list_append(device->pending_ops, cmd);
    mainloop_set_trigger(device->work);
}
