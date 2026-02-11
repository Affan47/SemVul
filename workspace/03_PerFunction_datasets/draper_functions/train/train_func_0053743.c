glusterd_rotate_gsync_logs (dict_t *dict, char **op_errstr, dict_t *rsp_dict)
{
        char               *slave   = NULL;
        char               *volname = NULL;
        char errmsg[1024]           = {0,};
        gf_boolean_t        exists  = _gf_false;
        glusterd_volinfo_t *volinfo = NULL;
        int                 ret     = 0;

        ret = dict_get_str (dict, "master", &volname);
        if (ret < 0) {
                ret = glusterd_rotate_gsync_all ();
                goto out;
        }

        exists = glusterd_check_volume_exists (volname);
        ret = glusterd_volinfo_find (volname, &volinfo);
        if ((ret) || (!exists)) {
                snprintf (errmsg, sizeof(errmsg), "Volume %s does not"
                          " exist", volname);
                gf_log ("", GF_LOG_WARNING, errmsg);
                *op_errstr = gf_strdup (errmsg);
                ret = -1;
                goto out;
        }

        ret = dict_get_str (dict, "slave", &slave);
        if (ret < 0) {
                ret = glusterd_do_gsync_log_rotation_mst (volinfo);
                goto out;
        }

        ret = glusterd_do_gsync_log_rotation_mst_slv (volinfo, slave, op_errstr);

 out:
        return ret;
}
