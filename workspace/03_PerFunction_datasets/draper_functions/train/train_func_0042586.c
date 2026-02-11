glusterd_op_verify_gsync_start_options (glusterd_volinfo_t *volinfo,
                                        char *slave, char **op_errstr)
{
        int                     ret = -1;
        gf_boolean_t            is_running = _gf_false;
        char                    msg[2048] = {0};
        uuid_t                  uuid = {0};
        glusterd_conf_t         *priv = NULL;
        xlator_t                *this = NULL;

        this = THIS;

        GF_ASSERT (volinfo);
        GF_ASSERT (slave);
        GF_ASSERT (op_errstr);
        GF_ASSERT (this && this->private);

        priv  = this->private;

        if (GLUSTERD_STATUS_STARTED != volinfo->status) {
                snprintf (msg, sizeof (msg), "Volume %s needs to be started "
                          "before "GEOREP" start", volinfo->volname);
                goto out;
        }


        ret = glusterd_gsync_get_uuid (slave, volinfo, uuid);
        if ((ret == 0) && (uuid_compare (priv->uuid, uuid) == 0)) {
                ret = glusterd_check_gsync_running_local (volinfo->volname,
                                                          slave, &is_running);
                if (ret) {
                        snprintf (msg, sizeof (msg), GEOREP" start option "
                                  "validation failed ");
                        goto out;
                }
                if (_gf_true == is_running) {
                        snprintf (msg, sizeof (msg), GEOREP " session between"
                                  " %s & %s already started", volinfo->volname,
                                  slave);
                        ret = -1;
                        goto out;
                }
        }
        ret = 0;
out:
        if (ret && (msg[0] != '\0')) {
                *op_errstr = gf_strdup (msg);
        }
        gf_log ("", GF_LOG_DEBUG, "Returning %d", ret);
        return ret;
}
