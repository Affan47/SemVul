glusterd_handle_log_rotate (rpcsvc_request_t *req)
{
        int32_t                 ret     = -1;
        gf_cli_req              cli_req = {{0,}};
        dict_t                 *dict    = NULL;
        glusterd_op_t           cli_op = GD_OP_LOG_ROTATE;
        char                   *volname = NULL;
        char                   msg[2048] = {0,};
        xlator_t               *this = NULL;

        GF_ASSERT (req);
        this = THIS;
        GF_ASSERT (this);

        ret = xdr_to_generic (req->msg[0], &cli_req, (xdrproc_t)xdr_gf_cli_req);
        if (ret < 0) {

                req->rpc_err = GARBAGE_ARGS;
                goto out;
        }

        if (cli_req.dict.dict_len) {

                dict  = dict_new ();

                ret = dict_unserialize (cli_req.dict.dict_val,
                                        cli_req.dict.dict_len,
                                        &dict);
                if (ret < 0) {
                        gf_log (this->name, GF_LOG_ERROR,
                                "failed to "
                                "unserialize req-buffer to dictionary");
                        snprintf (msg, sizeof (msg), "Unable to decode the "
                                  "command");
                        goto out;
                }
        }

        ret = dict_get_str (dict, "volname", &volname);
        if (ret) {
                snprintf (msg, sizeof (msg), "Failed to get volume name");
                gf_log (this->name, GF_LOG_ERROR, "%s", msg);
                goto out;
        }

        gf_log (this->name, GF_LOG_INFO, "Received log rotate req "
                "for volume %s", volname);

        ret = dict_set_uint64 (dict, "rotate-key", (uint64_t)time (NULL));
        if (ret)
                goto out;

        ret = glusterd_op_begin (req, GD_OP_LOG_ROTATE, dict,
                                 msg, sizeof (msg));

out:
        glusterd_friend_sm ();
        glusterd_op_sm ();

        if (ret) {
                if (msg[0] == '\0')
                        snprintf (msg, sizeof (msg), "Operation failed");
                ret = glusterd_op_send_cli_response (cli_op, ret, 0, req,
                                                     dict, msg);
        }

        free (cli_req.dict.dict_val);
        return ret;
}
