glusterd_op_sync_volume (dict_t *dict, char **op_errstr,
                         dict_t *rsp_dict)
{
        int                                     ret = -1;
        char                                    *volname = NULL;
        char                                    *hostname = NULL;
        char                                    msg[2048] = {0,};
        int                                     count = 1;
        int                                     vol_count = 0;
        glusterd_conf_t                         *priv = NULL;
        glusterd_volinfo_t                      *volinfo = NULL;
        xlator_t                                *this = NULL;

        this = THIS;
        GF_ASSERT (this);
        priv = this->private;
        GF_ASSERT (priv);

        ret = dict_get_str (dict, "hostname", &hostname);
        if (ret) {
                snprintf (msg, sizeof (msg), "hostname couldn't be "
                          "retrieved from msg");
                *op_errstr = gf_strdup (msg);
                goto out;
        }

        if (!glusterd_is_local_addr (hostname)) {
                ret = 0;
                goto out;
        }


        ret = dict_get_str (dict, "volname", &volname);
        if (!ret) {
                ret = glusterd_volinfo_find (volname, &volinfo);
                if (ret) {
                        gf_log ("", GF_LOG_ERROR, "Volume with name: %s "
                                "not exists", volname);
                        goto out;
                }
        }

        if (!rsp_dict) {

                ret = 0;
                goto out;
        }

        if (volname) {
                ret = glusterd_add_volume_to_dict (volinfo, rsp_dict,
                                                   1);
                vol_count = 1;
        } else {
                list_for_each_entry (volinfo, &priv->volumes, vol_list) {
                        ret = glusterd_add_volume_to_dict (volinfo,
                                                           rsp_dict, count);
                        if (ret)
                                goto out;

                        vol_count = count++;
                }
        }
        ret = dict_set_int32 (rsp_dict, "count", vol_count);

out:
        gf_log ("", GF_LOG_DEBUG, "Returning %d", ret);

        return ret;
}
