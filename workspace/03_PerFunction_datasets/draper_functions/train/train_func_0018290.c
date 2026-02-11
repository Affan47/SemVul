glusterd_op_stage_start_volume (dict_t *dict, char **op_errstr)
{
        int                                     ret = 0;
        char                                    *volname = NULL;
        int                                     flags = 0;
        gf_boolean_t                            exists = _gf_false;
        glusterd_volinfo_t                      *volinfo = NULL;
        glusterd_brickinfo_t                    *brickinfo = NULL;
        char                                    msg[2048];
        glusterd_conf_t                         *priv = NULL;

        priv = THIS->private;
        if (!priv) {
                gf_log ("glusterd", GF_LOG_ERROR,
                        "priv is NULL");
                ret = -1;
                goto out;
        }

        ret = glusterd_op_start_volume_args_get (dict, &volname, &flags);
        if (ret)
                goto out;

        exists = glusterd_check_volume_exists (volname);

        if (!exists) {
                snprintf (msg, sizeof (msg), "Volume %s does not exist", volname);
                gf_log ("", GF_LOG_ERROR, "%s",
                        msg);
                *op_errstr = gf_strdup (msg);
                ret = -1;
        } else {
                ret = 0;
        }

        ret  = glusterd_volinfo_find (volname, &volinfo);
        if (ret)
                goto out;

        list_for_each_entry (brickinfo, &volinfo->bricks, brick_list) {
                ret = glusterd_resolve_brick (brickinfo);
                if (ret) {
                        gf_log ("", GF_LOG_ERROR,
                                "Unable to resolve brick %s:%s",
                                brickinfo->hostname, brickinfo->path);
                        goto out;
                }

                if (!uuid_compare (brickinfo->uuid, priv->uuid)) {
                        ret = glusterd_brick_create_path (brickinfo->hostname,
                                                          brickinfo->path,
                                                          volinfo->volume_id,
                                                          0777, op_errstr);
                        if (ret)
                                goto out;
                }

                if (!(flags & GF_CLI_FLAG_OP_FORCE)) {
                        if (glusterd_is_volume_started (volinfo)) {
                                snprintf (msg, sizeof (msg), "Volume %s already"
                                          " started", volname);
                                gf_log ("glusterd", GF_LOG_ERROR, "%s", msg);
                                *op_errstr = gf_strdup (msg);
                                ret = -1;
                                goto out;
                        }
                }
        }

        ret = 0;
out:
        gf_log ("", GF_LOG_DEBUG, "Returning %d", ret);

        return ret;
}
