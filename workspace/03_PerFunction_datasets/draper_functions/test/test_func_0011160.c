mgmt_pmap_signout_cbk (struct rpc_req *req, struct iovec *iov, int count,
                       void *myframe)
{
        pmap_signout_rsp  rsp   = {0,};
        int              ret   = 0;
        glusterfs_ctx_t  *ctx = NULL;

        if (-1 == req->rpc_status) {
                rsp.op_ret   = -1;
                rsp.op_errno = EINVAL;
                goto out;
        }

        ctx = glusterfs_ctx_get ();
        ret = xdr_to_generic (*iov, &rsp, (xdrproc_t)xdr_pmap_signout_rsp);
        if (ret < 0) {
                gf_log (THIS->name, GF_LOG_ERROR, "XDR decoding failed");
                rsp.op_ret   = -1;
                rsp.op_errno = EINVAL;
                goto out;
        }

        if (-1 == rsp.op_ret) {
                gf_log (THIS->name, GF_LOG_ERROR,
                        "failed to register the port with glusterd");
                goto out;
        }
out:
        return 0;
}
