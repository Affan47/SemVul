glusterd_bricks_select_stop_volume (dict_t *dict, char **op_errstr,
                                    struct list_head *selected)
{
        int                                     ret = 0;
        int                                     flags = 0;
        char                                    *volname = NULL;
        glusterd_volinfo_t                      *volinfo = NULL;
        glusterd_brickinfo_t                    *brickinfo = NULL;
        glusterd_pending_node_t                 *pending_node = NULL;

        ret = glusterd_op_stop_volume_args_get (dict, &volname, &flags);
        if (ret)
                goto out;

        ret  = glusterd_volinfo_find (volname, &volinfo);
        if (ret) {
                gf_log (THIS->name, GF_LOG_ERROR, FMTSTR_CHECK_VOL_EXISTS,
                        volname);
                gf_asprintf (op_errstr, FMTSTR_CHECK_VOL_EXISTS, volname);
                goto out;
        }

        list_for_each_entry (brickinfo, &volinfo->bricks, brick_list) {
                if (glusterd_is_brick_started (brickinfo)) {
                        pending_node = GF_CALLOC (1, sizeof (*pending_node),
                                                  gf_gld_mt_pending_node_t);
                        if (!pending_node) {
                                ret = -1;
                                goto out;
                        } else {
                                pending_node->node = brickinfo;
                                pending_node->type = GD_NODE_BRICK;
                                list_add_tail (&pending_node->list, selected);
                                pending_node = NULL;
                        }
                }
        }

out:
        return ret;
}
