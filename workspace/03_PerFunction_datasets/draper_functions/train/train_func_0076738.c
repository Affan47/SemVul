volgen_graph_build_clients (volgen_graph_t *graph, glusterd_volinfo_t *volinfo,
                            dict_t *set_dict, void *param)
{
        int                      i                  = 0;
        int                      ret                = -1;
        uint32_t                 client_type        = GF_CLIENT_OTHER;
        char                     transt[16]         = {0,};
        char                    *volname            = NULL;
        char                    *str                = NULL;
        glusterd_brickinfo_t    *brick              = NULL;
        xlator_t                *xl                 = NULL;
        char                    *ssl_str            = NULL;
        gf_boolean_t             ssl_bool;

        volname = volinfo->volname;

        if (volinfo->brick_count == 0) {
                gf_log ("", GF_LOG_ERROR,
                        "volume inconsistency: brick count is 0");
                goto out;
        }

        if ((volinfo->dist_leaf_count < volinfo->brick_count) &&
            ((volinfo->brick_count % volinfo->dist_leaf_count) != 0)) {
                gf_log ("", GF_LOG_ERROR,
                        "volume inconsistency: "
                        "total number of bricks (%d) is not divisible with "
                        "number of bricks per cluster (%d) in a multi-cluster "
                        "setup",
                        volinfo->brick_count, volinfo->dist_leaf_count);
                goto out;
        }

        get_transport_type (volinfo, set_dict, transt, _gf_false);

        if (!strcmp (transt, "tcp,rdma"))
                strcpy (transt, "tcp");

        i = 0;
        ret = -1;
        list_for_each_entry (brick, &volinfo->bricks, brick_list) {
                ret = -1;
                xl = volgen_graph_add_nolink (graph, "protocol/client",
                                              "%s-client-%d", volname, i);
                if (!xl)
                        goto out;
                ret = xlator_set_option (xl, "remote-host", brick->hostname);
                if (ret)
                        goto out;
                ret = xlator_set_option (xl, "remote-subvolume", brick->path);
                if (ret)
                        goto out;
                ret = xlator_set_option (xl, "transport-type", transt);
                if (ret)
                        goto out;

                ret = dict_get_uint32 (set_dict, "trusted-client",
                                       &client_type);

                if (!ret && client_type == GF_CLIENT_TRUSTED) {
                        str = NULL;
                        str = glusterd_auth_get_username (volinfo);
                        if (str) {
                                ret = xlator_set_option (xl, "username",
                                                         str);
                                if (ret)
                                        goto out;
                        }

                        str = glusterd_auth_get_password (volinfo);
                        if (str) {
                                ret = xlator_set_option (xl, "password",
                                                         str);
                                if (ret)
                                        goto out;
                        }
                }

                if (dict_get_str(set_dict,"client.ssl",&ssl_str) == 0) {
                        if (gf_string2boolean(ssl_str,&ssl_bool) == 0) {
                                if (ssl_bool) {
                                        ret = xlator_set_option(xl,
                                                "transport.socket.ssl-enabled",
                                                "true");
                                        if (ret) {
                                                goto out;
                                        }
                                }
                        }
                }

                i++;
        }

        if (i != volinfo->brick_count) {
                gf_log ("", GF_LOG_ERROR,
                        "volume inconsistency: actual number of bricks (%d) "
                        "differs from brick count (%d)", i,
                        volinfo->brick_count);

                ret = -1;
                goto out;
        }
        ret = 0;
out:
        return ret;
}
