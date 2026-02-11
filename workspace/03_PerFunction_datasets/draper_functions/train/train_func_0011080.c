reconfigure (xlator_t *this, dict_t *options)
{
	clnt_conf_t *conf              = NULL;
	int          ret               = -1;
        int          subvol_ret        = 0;
        char        *old_remote_subvol = NULL;
        char        *new_remote_subvol = NULL;
        char        *old_remote_host   = NULL;
        char        *new_remote_host   = NULL;

	conf = this->private;

        GF_OPTION_RECONF ("frame-timeout", conf->rpc_conf.rpc_timeout,
                          options, int32, out);

        GF_OPTION_RECONF ("ping-timeout", conf->opt.ping_timeout,
                          options, int32, out);

        subvol_ret = dict_get_str (this->options, "remote-host",
                                   &old_remote_host);

        if (subvol_ret == 0) {
                subvol_ret = dict_get_str (options, "remote-host",
                                           &new_remote_host);
                if (subvol_ret == 0) {
                        if (strcmp (old_remote_host, new_remote_host)) {
                                ret = 1;
                                goto out;
                        }
                }
        }

        subvol_ret = dict_get_str (this->options, "remote-subvolume",
                                   &old_remote_subvol);

        if (subvol_ret == 0) {
                subvol_ret = dict_get_str (options, "remote-subvolume",
                                           &new_remote_subvol);
                if (subvol_ret == 0) {
                        if (strcmp (old_remote_subvol, new_remote_subvol)) {
                                ret = 1;
                                goto out;
                        }
                }
        }

        ret = client_init_grace_timer (this, options, conf);
        if (ret)
                goto out;

        ret = 0;
out:
	return ret;

}
