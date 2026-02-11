glusterd_handle_cli_profile_volume (rpcsvc_request_t *req)
{
        int32_t                         ret     = -1;
        gf_cli_req                      cli_req = {{0,}};
        dict_t                          *dict = NULL;
        glusterd_op_t                   cli_op = GD_OP_PROFILE_VOLUME;
        char                            *volname = NULL;
        int32_t                         op = 0;

        GF_ASSERT (req);

        if (!xdr_to_generic (req->msg[0], &cli_req, (xdrproc_t)xdr_gf_cli_req)) {

                req->rpc_err = GARBAGE_ARGS;
                goto out;
        }


        if (cli_req.dict.dict_len > 0) {
                dict = dict_new();
                if (!dict)
                        goto out;
                dict_unserialize (cli_req.dict.dict_val,
                                  cli_req.dict.dict_len, &dict);

        }

        ret = dict_get_str (dict, "volname", &volname);
        if (ret) {
                gf_log (THIS->name, GF_LOG_ERROR, "failed to get volname");
                goto out;
        }

        gf_log ("glusterd", GF_LOG_INFO, "Received volume profile req "
                "for volume %s", volname);
        ret = dict_get_int32 (dict, "op", &op);
        if (ret) {
                gf_log (THIS->name, GF_LOG_ERROR, "failed to get op");
                goto out;
        }

        gf_cmd_log ("Volume stats", "volume  : %s, op: %d", volname, op);
        ret = glusterd_op_begin (req, cli_op, dict);
        gf_cmd_log ("Volume stats", " on volume %s, op: %d %s ",
                    volname, op,
                    ((ret == 0)? " SUCCEDED":" FAILED"));

out:
        glusterd_friend_sm ();
        glusterd_op_sm ();

        if (ret && dict)
                dict_unref (dict);
        if (cli_req.dict.dict_val)
                free (cli_req.dict.dict_val);
        if (ret)
                ret = glusterd_op_send_cli_response (cli_op, ret, 0, req,
                                                     NULL, "operation failed");

        gf_log ("glusterd", GF_LOG_DEBUG, "Returning %d", ret);
        return ret;
}
