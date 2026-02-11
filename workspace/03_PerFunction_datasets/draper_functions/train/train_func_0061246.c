glusterd_op_stage_remove_brick (dict_t *dict, char **op_errstr)
{
        int                 ret         = -1;
        char               *volname     = NULL;
        glusterd_volinfo_t *volinfo     = NULL;
        char               *errstr      = NULL;
        int32_t             brick_count = 0;
        char                msg[2048]   = {0,};
        int32_t             flag        = 0;
        gf1_op_commands     cmd         = GF_OP_CMD_NONE;

        ret = dict_get_str (dict, "volname", &volname);
        if (ret) {
                gf_log ("", GF_LOG_ERROR, "Unable to get volume name");
                goto out;
        }

        ret = glusterd_volinfo_find (volname, &volinfo);

        if (ret) {
                gf_log ("", GF_LOG_ERROR, "Volume %s does not exist", volname);
                goto out;
        }

        ret = dict_get_int32 (dict, "command", &flag);
        if (ret) {
                gf_log ("", GF_LOG_ERROR, "Unable to get brick count");
                goto out;
        }
        cmd = flag;

        ret = -1;
        switch (cmd) {
        case GF_OP_CMD_NONE:
                errstr = gf_strdup ("no remove-brick command issued");
                goto out;

        case GF_OP_CMD_STATUS:
                ret = 0;
                goto out;

        case GF_OP_CMD_START:
        {
                if (GLUSTERD_STATUS_STARTED != volinfo->status) {
                        snprintf (msg, sizeof (msg), "Volume %s needs to be started "
                                  "before remove-brick (you can use 'force' or "
                                  "'commit' to override this behavior)",
                                  volinfo->volname);
                        errstr = gf_strdup (msg);
                        gf_log (THIS->name, GF_LOG_ERROR, "%s", errstr);
                        goto out;
                }
                if (glusterd_is_defrag_on(volinfo)) {
                        errstr = gf_strdup("Rebalance is in progress. Please retry"
                                           " after completion");
                        gf_log ("glusterd", GF_LOG_ERROR, "%s", errstr);
                        goto out;
                }
                break;
        }

        case GF_OP_CMD_PAUSE:
        case GF_OP_CMD_ABORT:
        {
                if (!volinfo->decommission_in_progress) {
                        errstr = gf_strdup("remove-brick is not in progress");
                        gf_log ("glusterd", GF_LOG_ERROR, "%s", errstr);
                        goto out;
                }
                break;
        }

        case GF_OP_CMD_COMMIT:
                if (volinfo->decommission_in_progress) {
                        errstr = gf_strdup ("use 'force' option as migration "
                                            "is in progress");
                        goto out;
                }
                break;

        case GF_OP_CMD_COMMIT_FORCE:
                break;
        }

        ret = dict_get_int32 (dict, "count", &brick_count);
        if (ret) {
                gf_log ("", GF_LOG_ERROR, "Unable to get brick count");
                goto out;
        }

        ret = 0;
        if (volinfo->brick_count == brick_count) {
                errstr = gf_strdup ("Deleting all the bricks of the "
                                    "volume is not allowed");
                ret = -1;
                goto out;
        }

out:
        gf_log ("", GF_LOG_DEBUG, "Returning %d", ret);
        if (ret && errstr) {
                if (op_errstr)
                        *op_errstr = errstr;
        }

        return ret;
}
