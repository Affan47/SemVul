glusterd_op_gsync_args_get (dict_t *dict, char **op_errstr,
                            char **master, char **slave)
{

        int             ret = -1;
        GF_ASSERT (dict);
        GF_ASSERT (op_errstr);
        GF_ASSERT (master);
        GF_ASSERT (slave);

        ret = dict_get_str (dict, "master", master);
        if (ret < 0) {
                gf_log ("", GF_LOG_WARNING, "master not found");
                *op_errstr = gf_strdup ("master not found");
                goto out;
        }

        ret = dict_get_str (dict, "slave", slave);
        if (ret < 0) {
                gf_log ("", GF_LOG_WARNING, "slave not found");
                *op_errstr = gf_strdup ("slave not found");
                goto out;
        }


        ret = 0;
out:
        gf_log ("", GF_LOG_DEBUG, "Returning %d", ret);
        return ret;
}
