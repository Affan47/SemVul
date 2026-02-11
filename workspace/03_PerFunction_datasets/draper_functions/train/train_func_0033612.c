client_query_portmap_cbk (struct rpc_req *req, struct iovec *iov, int count, void *myframe)
{
        struct pmap_port_by_brick_rsp     rsp   = {0,};
        call_frame_t                     *frame = NULL;
        clnt_conf_t                      *conf  = NULL;
        int                               ret   = -1;
        struct rpc_clnt_config            config = {0, };
        xlator_t                         *this   = NULL;

        frame = myframe;
        if (!frame || !frame->this || !frame->this->private) {
                gf_log (THIS->name, GF_LOG_WARNING,
                        "frame not found with rpc request");
                goto out;
        }
        this  = frame->this;
        conf  = frame->this->private;

        if (-1 == req->rpc_status) {
                gf_log (this->name, GF_LOG_WARNING,
                        "received RPC status error, try again later");
                goto out;
        }

        ret = xdr_to_generic (*iov, &rsp, (xdrproc_t)xdr_pmap_port_by_brick_rsp);
        if (ret < 0) {
                gf_log (this->name, GF_LOG_ERROR, "XDR decoding failed");
                goto out;
        }

        if (-1 == rsp.op_ret) {
                ret = -1;
                gf_log (this->name, ((!conf->portmap_err_logged) ?
                                     GF_LOG_ERROR : GF_LOG_DEBUG),
                        "failed to get the port number for remote subvolume. "
                        "Please run 'gluster volume status' on server to see "
                        "if brick process is running.");
                conf->portmap_err_logged = 1;
                goto out;
        }

        conf->portmap_err_logged = 0;

        config.remote_port = rsp.port;
        rpc_clnt_reconfig (conf->rpc, &config);

        conf->skip_notify = 1;
	conf->quick_reconnect = 1;

out:
        if (frame)
                STACK_DESTROY (frame->root);

        if (conf) {


                rpc_transport_disconnect (conf->rpc->conn.trans);
        }

        return ret;
}
