glusterd_handle_set_volume (rpcsvc_request_t *req)
{
        int32_t                         ret = -1;
        gf_cli_req                      cli_req = {{0,}};
        dict_t                          *dict = NULL;
        glusterd_op_t                   cli_op = GD_OP_SET_VOLUME;
        char                            *key = NULL;
        char                            *value = NULL;
        char                            *volname = NULL;

        GF_ASSERT (req);

        if (!xdr_to_generic (req->msg[0], &cli_req, (xdrproc_t)xdr_gf_cli_req)) {

                req->rpc_err = GARBAGE_ARGS;
                goto out;
        }

        if (cli_req.dict.dict_len) {

                dict  = dict_new ();

                ret = dict_unserialize (cli_req.dict.dict_val,
                                        cli_req.dict.dict_len,
                                        &dict);
                if (ret < 0) {
                        gf_log ("glusterd", GF_LOG_ERROR,
                                "failed to "
                                "unserialize req-buffer to dictionary");
                        goto out;
                } else {
                        dict->extra_stdfree = cli_req.dict.dict_val;
                }
        }

        ret = dict_get_str (dict, "volname", &volname);
        if (ret) {
                gf_log ("", GF_LOG_WARNING, "Unable to get volume name, while"
                        "handling volume set command");
                goto out;
        }

        ret = dict_get_str (dict, "key1", &key);
        if (ret) {
                if (strcmp (volname, "help-xml") && strcmp (volname, "help")) {
                        gf_log ("", GF_LOG_WARNING, "Unable to get key, while "
                                "handling volume set for %s",volname);
                        goto out;
                }
        }

        ret = dict_get_str (dict, "value1", &value);
        if (ret) {
                if (strcmp (volname, "help-xml") && strcmp (volname, "help")) {
                        gf_log ("", GF_LOG_WARNING, "Unable to get value, while"
                                "handling volume set for %s",volname);
                        goto out;
                }
        }


        gf_cmd_log ("volume set", "volume-name:%s: key:%s, value:%s",volname,
                    key, value);
        ret = glusterd_op_begin (req, GD_OP_SET_VOLUME, dict);
        gf_cmd_log ("volume set", "volume-name:%s: key:%s, value:%s %s",
                    volname, key, value, (ret == 0)? "SUCCEDED" : "FAILED" );
out:

        glusterd_friend_sm ();
        glusterd_op_sm ();

        if (ret) {
                if (dict)
                        dict_unref (dict);
                ret = glusterd_op_send_cli_response (cli_op, ret, 0, req,
                                                     NULL, "operation failed");
        }
        return ret;
}
