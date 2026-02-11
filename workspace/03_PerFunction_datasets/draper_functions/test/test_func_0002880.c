glusterfs_handle_translator_info_get (rpcsvc_request_t *req)
{
        int32_t                  ret     = -1;
        gd1_mgmt_brick_op_req    xlator_req = {0,};
        dict_t                   *dict    = NULL;
        xlator_t                 *this = NULL;
        gf1_cli_top_op           top_op = 0;
        uint32_t                 blk_size = 0;
        uint32_t                 blk_count = 0;
        gfd_vol_top_priv_t       *priv = NULL;
        pthread_t                tid = -1;

        GF_ASSERT (req);
        this = THIS;
        GF_ASSERT (this);

        ret = xdr_to_generic (req->msg[0], &xlator_req,
                              (xdrproc_t)xdr_gd1_mgmt_brick_op_req);
        if (ret < 0) {

                req->rpc_err = GARBAGE_ARGS;
                goto out;
        }
        dict = dict_new ();

        ret = dict_unserialize (xlator_req.input.input_val,
                                xlator_req.input.input_len,
                                &dict);
        if (ret < 0) {
                gf_log (this->name, GF_LOG_ERROR,
                        "failed to "
                        "unserialize req-buffer to dictionary");
                goto out;
        }

        priv = GF_MALLOC (sizeof (gfd_vol_top_priv_t), gfd_mt_vol_top_priv_t);
        if (!priv) {
                gf_log ("glusterd", GF_LOG_ERROR, "failed to allocate memory");
                goto out;
        }
        priv->xlator_req = xlator_req;
        priv->req = req;

        ret = dict_get_int32 (dict, "top-op", (int32_t *)&top_op);
        if ((!ret) && (GF_CLI_TOP_READ_PERF == top_op ||
            GF_CLI_TOP_WRITE_PERF == top_op)) {
                ret = dict_get_uint32 (dict, "blk-size", &blk_size);
                if (ret)
                        goto cont;
                ret = dict_get_uint32 (dict, "blk-cnt", &blk_count);
                if (ret)
                        goto cont;
                priv->blk_size = blk_size;
                priv->blk_count = blk_count;
                if (GF_CLI_TOP_READ_PERF == top_op) {
                        ret = pthread_create (&tid, NULL,
                                              glusterfs_volume_top_read_perf,
                                              priv);
                } else if ( GF_CLI_TOP_WRITE_PERF == top_op) {
                        ret = pthread_create (&tid, NULL,
                                              glusterfs_volume_top_write_perf,
                                              priv);
                }
                if (ret) {
                        gf_log ("glusterd", GF_LOG_ERROR,
                                "Thread create failed");
                        goto cont;
                }
                gf_log ("glusterd", GF_LOG_DEBUG, "Created new thread with "
                        "tid %u", (unsigned int)tid);
                goto out;
        }
cont:
        priv->throughput = 0;
        priv->time = 0;
        ret = glusterfs_handle_translator_info_get_cont (priv);
out:
        if (dict)
                dict_unref (dict);
        return ret;
}
