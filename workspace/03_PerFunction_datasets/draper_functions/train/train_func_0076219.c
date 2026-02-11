glusterd_gsync_configure (glusterd_volinfo_t *volinfo, char *slave,
                          dict_t *dict, dict_t *resp_dict, char **op_errstr)
{
        int32_t         ret     = -1;
        char            *op_name = NULL;
        char            *op_value = NULL;
        runner_t        runner    = {0,};
        glusterd_conf_t *priv   = NULL;
        char            *subop  = NULL;
        char            *master = NULL;

        GF_ASSERT (slave);
        GF_ASSERT (op_errstr);
        GF_ASSERT (dict);
        GF_ASSERT (resp_dict);

        ret = dict_get_str (dict, "subop", &subop);
        if (ret != 0)
                goto out;

        if (strcmp (subop, "get") == 0 || strcmp (subop, "get-all") == 0) {

                gf_log ("", GF_LOG_DEBUG, "Returning 0");
                return 0;
        }

        ret = dict_get_str (dict, "op_name", &op_name);
        if (ret != 0)
                goto out;

        if (strtail (subop, "set")) {
                ret = dict_get_str (dict, "op_value", &op_value);
                if (ret != 0)
                        goto out;
        }

        if (THIS)
                priv = THIS->private;
        if (priv == NULL) {
                gf_log ("", GF_LOG_ERROR, "priv of glusterd not present");
                *op_errstr = gf_strdup ("glusterd defunct");
                goto out;
        }

        master = "";
        runinit (&runner);
        runner_add_args (&runner, GSYNCD_PREFIX"/gsyncd", "-c", NULL);
        runner_argprintf (&runner, "%s/"GSYNC_CONF, priv->workdir);
        if (volinfo) {
                master = volinfo->volname;
                runner_argprintf (&runner, ":%s", master);
        }
        runner_add_arg (&runner, slave);
        runner_argprintf (&runner, "--config-%s", subop);
        runner_add_arg (&runner, op_name);
        if (op_value)
                runner_add_arg (&runner, op_value);
        synclock_unlock (&priv->big_lock);
        ret = runner_run (&runner);
        synclock_lock (&priv->big_lock);
        if (ret) {
                gf_log ("", GF_LOG_WARNING, "gsyncd failed to "
                        "%s %s option for %s %s peers",
                        subop, op_name, master, slave);

                gf_asprintf (op_errstr, GEOREP" config-%s failed for %s %s",
                             subop, master, slave);

                goto out;
        }
        ret = 0;
        gf_asprintf (op_errstr, "config-%s successful", subop);

out:
        if (!ret && volinfo) {
                ret = glusterd_check_restart_gsync_session (volinfo, slave,
                                                            resp_dict);
                if (ret)
                        *op_errstr = gf_strdup ("internal error");
        }

        gf_log ("", GF_LOG_DEBUG, "Returning %d", ret);
        return ret;
}
