glusterd_check_restart_gsync_session (glusterd_volinfo_t *volinfo, char *slave,
                                      dict_t *resp_dict)
{

        int                    ret = 0;
        uuid_t                 uuid = {0, };
        glusterd_conf_t        *priv = NULL;
        char                   *status_msg = NULL;

        GF_ASSERT (volinfo);
        GF_ASSERT (slave);
        GF_ASSERT (THIS);
        GF_ASSERT (THIS->private);

        priv = THIS->private;

        if (glusterd_gsync_get_uuid (slave, volinfo, uuid))

                goto out;
        if (uuid_compare (MY_UUID, uuid) == 0) {
                ret = stop_gsync (volinfo->volname, slave, &status_msg);
                if (ret == 0 && status_msg)
                        ret = dict_set_str (resp_dict, "gsync-status",
                                            status_msg);
                if (ret == 0)
                        ret = glusterd_start_gsync (volinfo, slave,
                                                    uuid_utoa(MY_UUID), NULL);
        }

 out:
        gf_log ("", GF_LOG_DEBUG, "Returning %d", ret);
        return ret;
}
