glusterd_op_status_volume (dict_t *dict, char **op_errstr,
                           dict_t *rsp_dict)
{
        int                     ret             = -1;
        int                     brick_count     = 0;
        int32_t                 brick_index     = 0;
        uint32_t                cmd             = 0;
        char                   *volname         = NULL;
        char                   *brick           = NULL;
        xlator_t               *this            = NULL;
        glusterd_volinfo_t     *volinfo         = NULL;
        glusterd_brickinfo_t   *brickinfo       = NULL;
        glusterd_brickinfo_t   *tmpbrickinfo    = NULL;
        glusterd_conf_t        *priv            = NULL;

        this = THIS;
        GF_ASSERT (this);
        priv = this->private;

        GF_ASSERT (priv);

        GF_ASSERT (dict);

        ret = dict_get_uint32 (dict, "cmd", &cmd);
        if (ret)
                goto out;

        if (!rsp_dict) {

                ret = 0;
                rsp_dict = glusterd_op_get_ctx ();

                if ((cmd & GF_CLI_STATUS_ALL)) {
                        ret = glusterd_get_all_volnames (rsp_dict);
                        if (ret)
                                gf_log (THIS->name, GF_LOG_ERROR,
                                        "failed to get all volume "
                                        "names for status");
                }

        }

        ret = dict_set_uint32 (rsp_dict, "cmd", cmd);
        if (ret)
                goto out;

        if (cmd & GF_CLI_STATUS_ALL)
                goto out;

        ret = dict_get_str (dict, "volname", &volname);
        if (ret)
                goto out;

        ret = glusterd_volinfo_find (volname, &volinfo);
        if (ret) {
                gf_log (THIS->name, GF_LOG_ERROR, "Volume with name: %s "
                        "does not exist", volname);
                goto out;
        }

        if ((cmd & GF_CLI_STATUS_BRICK) != 0) {
                ret = dict_get_str (dict, "brick", &brick);
                if (ret)
                        goto out;
                ret = glusterd_brickinfo_from_brick (brick, &tmpbrickinfo);
                if (ret)
                        goto out;
                if (uuid_is_null (tmpbrickinfo->uuid) &&
                    glusterd_resolve_brick (tmpbrickinfo))
                        goto out;
        }

        list_for_each_entry (brickinfo, &volinfo->bricks, brick_list) {
                if (!uuid_compare (brickinfo->uuid, priv->uuid)) {

                        if ((cmd & GF_CLI_STATUS_BRICK) != 0 &&
                            (strcmp (tmpbrickinfo->path,
                                     brickinfo->path) ||
                             uuid_compare (tmpbrickinfo->uuid,
                                           brickinfo->uuid)))
                                continue;

                        glusterd_add_brick_to_dict (volinfo, brickinfo,
                                                    rsp_dict, brick_index);

                        if (cmd & GF_CLI_STATUS_DETAIL)
                                glusterd_add_brick_detail_to_dict (volinfo,
                                                                   brickinfo,
                                                                   rsp_dict,
                                                                   brick_index);
                        brick_count++;
                }
                if (!(cmd & GF_CLI_STATUS_BRICK))
                        brick_index++;
        }

        ret = dict_set_int32 (rsp_dict, "count", brick_count);

out:
        gf_log (THIS->name, GF_LOG_DEBUG, "Returning %d", ret);

        return ret;
}
