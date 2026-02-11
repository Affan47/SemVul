lrmd_rsc_execute_stonith(lrmd_rsc_t * rsc, lrmd_cmd_t * cmd)
{
    int rc = 0;
    int do_monitor = 0;

    stonith_t *stonith_api = get_stonith_connection();

    if (!stonith_api) {
        cmd->exec_rc = get_uniform_rc("stonith", cmd->action, -ENOTCONN);
        cmd->lrmd_op_status = PCMK_LRM_OP_ERROR;
        cmd_finalize(cmd, rsc);
        return -EUNATCH;
    }

    if (safe_str_eq(cmd->action, "start")) {
        char *key = NULL;
        char *value = NULL;
        stonith_key_value_t *device_params = NULL;

        if (cmd->params) {
            GHashTableIter iter;

            g_hash_table_iter_init(&iter, cmd->params);
            while (g_hash_table_iter_next(&iter, (gpointer *) & key, (gpointer *) & value)) {
                device_params = stonith_key_value_add(device_params, key, value);
            }
        }


        rc = stonith_api->cmds->register_device(stonith_api,
                                                st_opt_sync_call,
                                                cmd->rsc_id,
                                                rsc->provider, rsc->type, device_params);

        stonith_key_value_freeall(device_params, 1, 1);
        if (rc == 0) {
            do_monitor = 1;
        }
    } else if (safe_str_eq(cmd->action, "stop")) {
        rc = stonith_api->cmds->remove_device(stonith_api, st_opt_sync_call, cmd->rsc_id);
        rsc->stonith_started = 0;
    } else if (safe_str_eq(cmd->action, "monitor")) {
        if (cmd->interval) {
            do_monitor = 1;
        } else {
            rc = rsc->stonith_started ? 0 : -ENODEV;
        }
    }

    if (!do_monitor) {
        goto cleanup_stonith_exec;
    }

    rc = stonith_api->cmds->monitor(stonith_api, 0, cmd->rsc_id, cmd->timeout / 1000);

    rc = stonith_api->cmds->register_callback(stonith_api,
                                              rc,
                                              0,
                                              0,
                                              cmd, "lrmd_stonith_callback", lrmd_stonith_callback);


    if (rc > 0) {
        rsc->active = cmd;
        return rc;
    } else if (rc == 0) {
        rc = -1;
    }

  cleanup_stonith_exec:
    stonith_action_complete(cmd, rc);
    return rc;
}
