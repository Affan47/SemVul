glusterd_op_stage_log_rotate (dict_t *dict, char **op_errstr)
{
        int                                     ret = -1;
        char                                    *volname = NULL;
        glusterd_volinfo_t                      *volinfo = NULL;
        gf_boolean_t                            exists = _gf_false;
        char                                    msg[2048] = {0};
        char                                    *brick = NULL;

        ret = dict_get_str (dict, "volname", &volname);
        if (ret) {
                gf_log ("", GF_LOG_ERROR, "Unable to get volume name");
                goto out;
        }

        exists = glusterd_check_volume_exists (volname);
        ret = glusterd_volinfo_find (volname, &volinfo);
        if (!exists) {
                snprintf (msg, sizeof (msg), "Volume %s does not exist",
                          volname);
                gf_log ("", GF_LOG_ERROR, "%s", msg);
                *op_errstr = gf_strdup (msg);
                ret = -1;
                goto out;
        }

        if (_gf_false == glusterd_is_volume_started (volinfo)) {
                snprintf (msg, sizeof (msg), "Volume %s needs to be started before"
                          " log rotate.", volname);
                gf_log ("", GF_LOG_ERROR, "%s", msg);
                *op_errstr = gf_strdup (msg);
                ret = -1;
                goto out;
        }

        ret = dict_get_str (dict, "brick", &brick);


        if (ret) {
                ret = 0;
                goto out;
        }

        if (strchr (brick, ':')) {
                ret = glusterd_volume_brickinfo_get_by_brick (brick, volinfo, NULL,
                                                              GF_PATH_COMPLETE);
                if (ret) {
                        snprintf (msg, sizeof (msg), "Incorrect brick %s "
                                  "for volume %s", brick, volname);
                        gf_log ("", GF_LOG_ERROR, "%s", msg);
                        *op_errstr = gf_strdup (msg);
                        goto out;
                }
        }
out:
        gf_log ("", GF_LOG_DEBUG, "Returning %d", ret);

        return ret;
}
