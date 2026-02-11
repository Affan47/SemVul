glusterfs_xlator_op_response_send (rpcsvc_request_t *req, int op_ret,
                                   char *msg, dict_t *output)
{
        gd1_mgmt_brick_op_rsp    rsp = {0,};
        int                      ret = -1;
        gf_boolean_t             free_ptr = _gf_false;
        GF_ASSERT (req);

        rsp.op_ret = op_ret;
        rsp.op_errno = 0;
        if (op_ret && msg && msg[0])
                rsp.op_errstr = msg;
        else
                rsp.op_errstr = "";

        if (output) {
                ret = dict_allocate_and_serialize (output,
                                                   &rsp.output.output_val,
                                                   &rsp.output.output_len);
        }
        if (!ret)
                free_ptr = _gf_true;

        ret = glusterfs_submit_reply (req, &rsp, NULL, 0, NULL,
                                     (xdrproc_t)xdr_gd1_mgmt_brick_op_rsp);

        if (free_ptr)
                GF_FREE (rsp.output.output_val);

        return ret;
}
