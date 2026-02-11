_get_client_op_versions (gf_getspec_req *args, peer_info_t *peerinfo)
{
        int    ret                   = 0;
        int    client_max_op_version = 1;
        int    client_min_op_version = 1;
        dict_t *dict                 = NULL;

        GF_ASSERT (args);
        GF_ASSERT (peerinfo);

        if (args->xdata.xdata_len) {
                dict = dict_new ();
                if (!dict) {
                        ret = -1;
                        goto out;
                }

                ret = dict_unserialize (args->xdata.xdata_val,
                                        args->xdata.xdata_len, &dict);
                if (ret) {
                        gf_log ("glusterd", GF_LOG_ERROR,
                                "Failed to unserialize request dictionary");
                        goto out;
                }

                ret = dict_get_int32 (dict, "min-op-version",
                                      &client_min_op_version);
                if (ret) {
                        gf_log ("glusterd", GF_LOG_ERROR,
                                "Failed to get client-min-op-version");
                        goto out;
                }

                ret = dict_get_int32 (dict, "max-op-version",
                                      &client_max_op_version);
                if (ret) {
                        gf_log ("glusterd", GF_LOG_ERROR,
                                "Failed to get client-max-op-version");
                        goto out;
                }
        }

        peerinfo->max_op_version = client_max_op_version;
        peerinfo->min_op_version = client_min_op_version;

out:
        return ret;
}
