glusterd_op_rebalance (dict_t *dict, char **op_errstr, dict_t *rsp_dict)
{
        char               *volname   = NULL;
        int                 ret       = 0;
        int32_t             cmd       = 0;
        char                msg[2048] = {0};
        glusterd_volinfo_t *volinfo   = NULL;
        uint64_t            files     = 0;
        uint64_t            size      = 0;
        void               *node_uuid = NULL;
        glusterd_conf_t    *priv      = NULL;
        dict_t             *tmp_dict  = NULL;

        priv = THIS->private;

        ret = dict_get_str (dict, "volname", &volname);
        if (ret) {
                gf_log (THIS->name, GF_LOG_DEBUG, "volname not given");
                goto out;
        }

        ret = dict_get_int32 (dict, "rebalance-command", &cmd);
        if (ret) {
                gf_log (THIS->name, GF_LOG_DEBUG, "command not given");
                goto out;
        }

        ret = glusterd_rebalance_cmd_validate (cmd, volname, &volinfo,
                                               msg, sizeof (msg));
        if (ret) {
                gf_log (THIS->name, GF_LOG_DEBUG, "cmd validate failed");
                goto out;
        }

        if ((cmd != GF_DEFRAG_CMD_STATUS) &&
            (cmd != GF_DEFRAG_CMD_STOP)) {
                ret = dict_get_ptr (dict, "node-uuid", &node_uuid);
                if (ret) {
                        gf_log (THIS->name, GF_LOG_DEBUG, "node-uuid not found");
                        goto out;
                }


                if (uuid_compare (node_uuid, priv->uuid)) {
                        gf_log (THIS->name, GF_LOG_DEBUG,
                                "not the source node %s", uuid_utoa (priv->uuid));
                        goto out;
                }
        }

        switch (cmd) {
        case GF_DEFRAG_CMD_START:
        case GF_DEFRAG_CMD_START_LAYOUT_FIX:
        case GF_DEFRAG_CMD_START_MIGRATE_DATA:
        case GF_DEFRAG_CMD_START_MIGRATE_DATA_FORCE:
                ret = glusterd_handle_defrag_start (volinfo, msg, sizeof (msg),
                                                    cmd, NULL);
                 break;
         case GF_DEFRAG_CMD_STOP:
                 ret = glusterd_defrag_stop (volinfo, &files, &size,
                                             msg, sizeof (msg));
                if (!ret && rsp_dict) {
                        ret = dict_set_uint64 (rsp_dict, "files", files);
                        if (ret)
                                gf_log (THIS->name, GF_LOG_WARNING,
                                        "failed to set file count");

                        ret = dict_set_uint64 (rsp_dict, "size", size);
                        if (ret)
                                gf_log (THIS->name, GF_LOG_WARNING,
                                        "failed to set xfer size");


                        ret = 0;
                }
                break;
        case GF_DEFRAG_CMD_STATUS:

                if (rsp_dict)
                        tmp_dict = rsp_dict;


                if (!tmp_dict)
                        tmp_dict = glusterd_op_get_ctx (GD_OP_REBALANCE);

                ret = glusterd_defrag_status_get (volinfo, tmp_dict);
                break;
        default:
                break;
        }

        glusterd_rebalance_cmd_log (cmd, volname, ret);

out:
        if (ret && op_errstr && msg[0])
                *op_errstr = gf_strdup (msg);

        return ret;
}
