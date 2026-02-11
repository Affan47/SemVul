glusterd_op_stage_validate (glusterd_op_t op, dict_t *dict, char **op_errstr,
                            dict_t *rsp_dict)
{
        int ret = -1;

        switch (op) {
                case GD_OP_CREATE_VOLUME:
                        ret = glusterd_op_stage_create_volume (dict, op_errstr);
                        break;

                case GD_OP_START_VOLUME:
                        ret = glusterd_op_stage_start_volume (dict, op_errstr);
                        break;

                case GD_OP_STOP_VOLUME:
                        ret = glusterd_op_stage_stop_volume (dict, op_errstr);
                        break;

                case GD_OP_DELETE_VOLUME:
                        ret = glusterd_op_stage_delete_volume (dict, op_errstr);
                        break;

                case GD_OP_ADD_BRICK:
                        ret = glusterd_op_stage_add_brick (dict, op_errstr);
                        break;

                case GD_OP_REPLACE_BRICK:
                        ret = glusterd_op_stage_replace_brick (dict, op_errstr,
                                                               rsp_dict);
                        break;

                case GD_OP_SET_VOLUME:
                        ret = glusterd_op_stage_set_volume (dict, op_errstr);
                        break;

                case GD_OP_RESET_VOLUME:
                        ret = glusterd_op_stage_reset_volume (dict, op_errstr);
                        break;

                case GD_OP_REMOVE_BRICK:
                        ret = glusterd_op_stage_remove_brick (dict, op_errstr);
                        break;

                case GD_OP_LOG_ROTATE:
                        ret = glusterd_op_stage_log_rotate (dict, op_errstr);
                        break;

                case GD_OP_SYNC_VOLUME:
                        ret = glusterd_op_stage_sync_volume (dict, op_errstr);
                        break;

                case GD_OP_GSYNC_SET:
                        ret = glusterd_op_stage_gsync_set (dict, op_errstr);
                        break;

                case GD_OP_PROFILE_VOLUME:
                        ret = glusterd_op_stage_stats_volume (dict, op_errstr);
                        break;

                case GD_OP_QUOTA:
                        ret = glusterd_op_stage_quota (dict, op_errstr);
                        break;

                case GD_OP_STATUS_VOLUME:
                        ret = glusterd_op_stage_status_volume (dict, op_errstr);
                        break;

                case GD_OP_REBALANCE:
                case GD_OP_DEFRAG_BRICK_VOLUME:
                        ret = glusterd_op_stage_rebalance (dict, op_errstr);
                        break;

                case GD_OP_HEAL_VOLUME:
                        ret = glusterd_op_stage_heal_volume (dict, op_errstr);
                        break;

                case GD_OP_STATEDUMP_VOLUME:
                        ret = glusterd_op_stage_statedump_volume (dict,
                                                                  op_errstr);
                        break;
                case GD_OP_CLEARLOCKS_VOLUME:
                        ret = glusterd_op_stage_clearlocks_volume (dict,
                                                                   op_errstr);
                        break;

                default:
                        gf_log ("", GF_LOG_ERROR, "Unknown op %d",
                                op);
        }

        gf_log ("", GF_LOG_DEBUG, "Returning %d", ret);

        return ret;
}
