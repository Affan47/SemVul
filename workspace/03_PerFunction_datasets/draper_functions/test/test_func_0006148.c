gf_cli3_1_status_volume (call_frame_t *frame, xlator_t *this,
                         void *data)
{
        gf_cli_req                      req  = {{0,}};
        int                             ret  = -1;
        dict_t                         *dict = NULL;

        if (!frame || !this || !data)
                goto out;

        dict = data;

        ret = dict_allocate_and_serialize (dict,
                                           &req.dict.dict_val,
                                           (size_t *)&req.dict.dict_len);
        if (ret < 0) {
                gf_log ("cli", GF_LOG_ERROR,
                        "failed to serialize the data");

                goto out;
        }
        ret = cli_cmd_submit (&req, frame, cli_rpc_prog,
                              GLUSTER_CLI_STATUS_VOLUME, NULL,
                              this, gf_cli3_1_status_cbk,
                              (xdrproc_t)xdr_gf_cli_req);

 out:
        gf_log ("cli", GF_LOG_DEBUG, "Returning: %d", ret);
        return ret;
}
